//
//  queue.c
//  libowl
//
//  Created by Rahul Gupta on 27/09/22.
//

#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"
#include "singly_linked_list.h"

/* Opaque type */

typedef struct queue
{
    owl_sll_t *_internal_list;
    size_t size;
    u_long max_capacity;
    u_long n_items;
} owl_queue_t;

//

owl_queue_t *owl_queue_init(size_t size, u_long capacity)
{
    owl_queue_t *queue = malloc(sizeof(owl_queue_t));
    queue->_internal_list = owl_sll_init(size);
    queue->size = size;
    queue->max_capacity = capacity;
    queue->n_items = 0;
    return queue;
}

void owl_queue_destroy(owl_queue_t *queue)
{
    owl_sll_destroy(queue->_internal_list);
    free(queue);
}

int owl_queue_enqueue(owl_queue_t *queue, void *data)
{
    if (queue->max_capacity == queue->n_items) return -1;
    owl_sll_binsert(queue->_internal_list, data);
    queue->n_items = owl_sll_length(queue->_internal_list);
    return 0;
}

void *owl_queue_dequeue(owl_queue_t *queue)
{
    void *data = owl_sll_fremove(queue->_internal_list);
    queue->n_items = owl_sll_length(queue->_internal_list);
    return data;
}


bool owl_queue_is_empty(owl_queue_t *queue)
{
    return queue->n_items == 0;
}

bool owl_queue_is_full(owl_queue_t *queue)
{
    return queue->n_items == queue->max_capacity;
}

// Getters

u_long owl_queue_max_capacity(owl_queue_t *queue)
{
    return queue->max_capacity;
}

u_long owl_queue_n_items(owl_queue_t *queue)
{
    return queue->n_items;
}

