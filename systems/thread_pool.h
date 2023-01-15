#ifndef thread_pool_h
#define thread_pool_h

#include "../collections/queue.h"
#include <pthread.h>
#include <sys/types.h>

typedef struct __opaq_owl__thread_job
{
    void *(*execute)(void *arg);
    void *arg;
} owl_thread_job_t;

typedef struct __opaq_owl__thread_pool owl_thread_pool_t;

owl_thread_pool_t *owl_thread_pool_init(int num_threads);
void owl_thread_pool_free(owl_thread_pool_t *tp);
owl_thread_job_t owl_thread_job_init(void *(*job)(void *arg), void *arg);
int owl_thread_pool_enqueue_work(owl_thread_pool_t *tp, owl_thread_job_t thread_job);

#endif /* thread_pool_h */
