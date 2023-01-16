# thread_pool.c

[Thread Pool](https://en.wikipedia.org/wiki/Thread_pool) implementation in c.

## Example

```c
#include "owl.h"
#include <stdio.h>
#include <unistd.h>

void *task1(void *arg)
{
    owl_println("Task 1 Begin");
    sleep(5);
    owl_println("Task 1 completed.");
    return NULL;
}
void *task2(void *arg)
{
    owl_println("Task 2 Begin");
    sleep(8);
    owl_println("Task 2 completed.");
    return NULL;
}
void *task3(void *arg)
{
    owl_println("Task 3 Begin");
    sleep(2);
    owl_println("Task 3 completed.");
    return NULL;
}

int main(int argc, const char *argv[])
{
    // Inititalize the thread pool with 2 threads
    owl_thread_pool_t *tp = owl_thread_pool_init(2);

    // Create and Enqueue the tasks into the thread pool. The first
    // argument is the pointer to a function and the second argument
    // is an optional argument to pass to that function when it is
    // executed.
    owl_worker_task_t t1 = owl_worker_task_init(task1, NULL);
    owl_worker_task_t t2 = owl_worker_task_init(task2, NULL);
    owl_worker_task_t t3 = owl_worker_task_init(task3, NULL);
    owl_thread_pool_enqueue_task(tp, t1);
    owl_thread_pool_enqueue_task(tp, t2);
    owl_thread_pool_enqueue_task(tp, t3);

    // Free will wait for the threads to complete all of the
    // tasks in the work queue
    owl_thread_pool_free(tp);

    printf("OWL 🦉\n");
}
```

## Functions

### Basics

```sh
owl_thread_pool_init            # allocate a new thread pool
owl_thread_pool_free            # deallocate the thread pool
owl_worker_task_init            # create a task
owl_thread_pool_enqueue_task    # enqueue the task
```

## API

```c
owl_thread_pool_t *owl_thread_pool_init(int num_threads);
void owl_thread_pool_free(owl_thread_pool_t *tp);
owl_worker_task_t owl_worker_task_init(void *(*execute)(void *arg), void *arg);
int owl_thread_pool_enqueue_task(owl_thread_pool_t *tp, owl_worker_task_t worker_task);
```
