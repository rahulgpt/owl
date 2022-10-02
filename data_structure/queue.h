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

typedef struct queue owl_queue_t;

owl_queue_t *owl_queue_init(size_t size, u_long capacity);
void owl_queue_destroy(owl_queue_t *queue);
int owl_queue_enqueue(owl_queue_t *queue, void *data);
void *owl_queue_dequeue(owl_queue_t *queue);
bool owl_queue_is_empty(owl_queue_t *queue);
bool owl_queue_is_full(owl_queue_t *queue);

// Getters

u_long owl_queue_max_capacity(owl_queue_t *queue);
u_long owl_queue_n_items(owl_queue_t *queue);

#endif /* queue_h */
