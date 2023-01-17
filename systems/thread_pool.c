#include "thread_pool.h"
#include "../utils/panic.h"
#include <limits.h>
#include <string.h>
#include <unistd.h>

#define MAX_THREADS 1024

static void *worker_fn(void *arg);

typedef struct __opaq_owl__thread_pool
{
    u_int num_threads;
    short int active;
    owl_queue_t *work_q;
    pthread_t *worker_pool;
    pthread_mutex_t lock;
    pthread_cond_t signal;
} owl_thread_pool_t;

owl_thread_pool_t *owl_thread_pool_init(int num_threads)
{
    owl_thread_pool_t *tp = calloc(1, sizeof(owl_thread_pool_t));

    tp->num_threads = num_threads;

    if (num_threads < 1)
        tp->num_threads = 1;

    if (num_threads > MAX_THREADS)
        tp->num_threads = MAX_THREADS;

    tp->active = 1;
    tp->lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    tp->signal = (pthread_cond_t)PTHREAD_COND_INITIALIZER;
    tp->work_q = owl_queue_init(sizeof(owl_worker_task_t), SIZE_MAX, NULL);

    pthread_mutex_lock(&tp->lock);
    tp->worker_pool = calloc(num_threads, sizeof(pthread_t));
    for (int i = 0; i < num_threads; i++)
    {

        int ret = pthread_create(&tp->worker_pool[i], NULL, worker_fn, tp);
        if (ret != 0)
            owl_panic("Error while creating threads");
    }
    pthread_mutex_unlock(&tp->lock);

    return tp;
}

void owl_thread_pool_free(owl_thread_pool_t *tp)
{
    if (!tp) owl_panic("Thread Pool is Null");

    tp->active = 0;

    pthread_cond_broadcast(&tp->signal);

    for (int i = 0; i < tp->num_threads; i++)
        pthread_join(tp->worker_pool[i], NULL);

    owl_queue_free(tp->work_q);
    free(tp->worker_pool);
    free(tp);
}

static void *worker_fn(void *arg)
{
    owl_thread_pool_t *tp = arg;
    owl_worker_task_t *task = NULL;

    while (!owl_queue_is_empty(tp->work_q) || tp->active == 1)
    {
        pthread_mutex_lock(&tp->lock);

        if (tp->active && owl_queue_is_empty(tp->work_q))
            pthread_cond_wait(&tp->signal, &tp->lock);

        task = owl_queue_dequeue(tp->work_q);

        pthread_mutex_unlock(&tp->lock);
        if (task != NULL && task->execute) task->execute(task->arg);
        free(task);
    }

    return NULL;
}

owl_worker_task_t owl_worker_task_init(void *(*execute)(void *arg), void *arg)
{
    owl_worker_task_t task;
    task.execute = execute;
    task.arg = arg;
    return task;
}

int owl_thread_pool_enqueue_task(owl_thread_pool_t *tp, owl_worker_task_t *worker_task)
{
    if (!tp) owl_panic("Thread Pool is Null");
    pthread_mutex_lock(&tp->lock);
    int status = owl_queue_enqueue(tp->work_q, worker_task);
    pthread_mutex_unlock(&tp->lock);
    pthread_cond_signal(&tp->signal);
    return status;
}