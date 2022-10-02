//
//  queue.h
//  libowl
//
//  Created by Rahul Gupta on 27/09/22.
//

#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdbool.h>
#include "singly_linked_list.h"

typedef struct
{
    bool empty;
    owl_sll_t *_internal_list;
    size_t size;
} owl_queue_t;

owl_queue_t *owl_queue_init(size_t size);
void owl_queue_destroy(owl_queue_t *queue);
void owl_queue_enqueue(owl_queue_t *queue, void *data);
void *owl_queue_dequeue(owl_queue_t *queue);

#endif /* queue_h */
