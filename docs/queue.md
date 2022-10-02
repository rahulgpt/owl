# q.c

[Queue](https://en.wikipedia.org/wiki/Queue_(abstract_data_type)) implementation in c.

## Example

```c
#include <stdio.h>
#include "queue.h"

typedef struct
{
    int id;
} job_t;

int main(int argc, const char* argv[]) {
    job_t job = {1};
    job_t job2 = {2};
    job_t job3 = {3};

    // Initializing a queue where each item is `job_t`. The first argument
    // is the size of the data and the second argument is the max capacity
    // of the queue.
    owl_queue_t *queue = owl_queue_init(sizeof(job_t), 3);

    // Enqueue three jobs in the queue.
    owl_queue_enqueue(queue, &job);
    owl_queue_enqueue(queue, &job2);
    owl_queue_enqueue(queue, &job3);


    // Enqueueing the fourth job will result in a bad status (-1).
    // If the job is enqueud the function will return 0.
    int status = owl_queue_enqueue(queue, &job2);
    printf("status: %d\n", status);

    // Checking the items in the queue
    printf("n_items: %lu\n", owl_queue_n_items(queue));

    owl_queue_dequeue(queue);
    owl_queue_dequeue(queue);
    owl_queue_dequeue(queue);

    // Dequeue will return `NULL` if the queue is empty.
    job_t *data = owl_queue_dequeue(queue);
    data ? printf("job_id: %d\n", data->id) : printf("NULL\n");

    owl_queue_destroy(queue);
}


/* Ouput
status: -1
n_items: 3
NULL
*/

```

## Functions

### Basics

```sh
owl_queue_init         # allocate a new queue
owl_queue_destroy      # deallocate the queue
owl_queue_enqueue      # enqueue data in the queue
owl_queue_dequeue      # dequeue data from the queue
owl_queue_is_empty     # check if the queue is empty
owl_queue_is_full      # check if the queue is full
```

### Getters

```sh
owl_queue_max_capacity  # get the max capacity
owl_queue_n_items       # get the current no of items
```

## API

```c
owl_queue_t *owl_queue_init(size_t size, u_long capacity); // return an opaque handle to the queue. The first argument is the size of the data.
void owl_queue_destroy(owl_queue_t *queue);
int owl_queue_enqueue(owl_queue_t *queue, void *data);
void *owl_queue_dequeue(owl_queue_t *queue);
bool owl_queue_is_empty(owl_queue_t *queue);
bool owl_queue_is_full(owl_queue_t *queue);

// Getters
u_long owl_queue_max_capacity(owl_queue_t *queue);
u_long owl_queue_n_items(owl_queue_t *queue);
```

