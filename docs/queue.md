# q.c

[Queue](<https://en.wikipedia.org/wiki/Queue_(abstract_data_type)>) implementation in c.

## Example

```c
#include <stdio.h>
#include "queue.h"

typedef struct
{
    int id;
} job_t;

void format(void *data) {
    job_t *d = data;
    printf("%d", d->id);
}

int main(int argc, const char* argv[]) {
    // Initializing a queue where each item is `job_t`. The first argument
    // is the size of the data and the second argument is the max capacity
    // of the queue.
    owl_queue_t *queue = owl_queue_init(sizeof(job_t), 3);

    // Enqueue three jobs in the queue. Enqueue operations performs a
    // copy of the data.
    owl_queue_enqueue(queue, &(job_t){ .id=1 });
    owl_queue_enqueue(queue, &(job_t){ .id=2 });
    owl_queue_enqueue(queue, &(job_t){ .id=3 });

    // Enqueueing the fourth job will result in a bad status (-1).
    // If the job is enqueud the function will return 0.
    int status = owl_queue_enqueue(queue, &(job_t){ .id=4 });
    printf("status: %d\n", status);

    // Checking the items in the queue
    printf("n_items: %zu\n", owl_queue_n_items(queue));

    // print the state of the queue
    owl_queue_print(queue, format, NULL);

    // Dequeu will return the pointer to the data on the heap.
    // We have to free the data after we are done.
    free(owl_queue_dequeue(queue));
    free(owl_queue_dequeue(queue));
    free(owl_queue_dequeue(queue));

    // Dequeue will return `NULL` if the queue is empty.
    job_t *data = owl_queue_dequeue(queue);
    data ? printf("job_id: %d\n", data->id) : printf("NULL\n");

    owl_queue_free(queue);
}


/* Ouput
status: -1
n_items: 3
| 1 | 2 | 3 |
NULL
*/

```

## Functions

### Basics

```sh
owl_queue_init         # allocate a new queue
owl_queue_free         # deallocate the queue
owl_queue_enqueue      # enqueue data in the queue
owl_queue_dequeue      # dequeue data from the queue
owl_sll_print          # print the state of the queue
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
owl_queue_t *owl_queue_init(size_t el_size, size_t capacity, void (*el_free)(void *data)); // returns a handle to the list
void owl_queue_free(owl_queue_t *queue);
int owl_queue_enqueue(owl_queue_t *queue, void *data);
void *owl_queue_dequeue(owl_queue_t *queue);
bool owl_queue_is_empty(owl_queue_t *queue);
bool owl_queue_is_full(owl_queue_t *queue);
void owl_queue_print(owl_queue_t *queue, void (*format)(void *data), char *connection_sym);

// Getters
size_t owl_queue_max_capacity(owl_queue_t *queue);
size_t owl_queue_n_items(owl_queue_t *queue);
```
