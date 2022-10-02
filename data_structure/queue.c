//
//  queue.c
//  libowl
//
//  Created by Rahul Gupta on 27/09/22.
//

#include "queue.h"
#include "singly_linked_list.h"
#include <stdlib.h>
#include <stdbool.h>

owl_queue_t *owl_queue_init(size_t size)
{
    owl_queue_t *queue = malloc(sizeof(owl_queue_t));
    queue->size = size;
    queue->empty = true;
    queue->_internal_list = owl_sll_init(size);
    return queue;
}

void owl_queue_destroy(owl_queue_t *queue)
{
    owl_sll_destroy(queue->_internal_list);
    free(queue);
}

void owl_queue_enqueue(owl_queue_t *queue, void *data)
{
    owl_sll_finsert(queue->_internal_list, data);
}

void *owl_queue_dequeue(owl_queue_t *queue)
{
    return owl_sll_bremove(queue->_internal_list);
}

