#include "queue.h"
#include "singly_linked_list.h"
#include <stdbool.h>
#include <stdlib.h>

/* Opaque type */

typedef struct __opaq_owl__queue
{
    owl_sll_t *_internal_list;
    size_t el_size;
    size_t max_capacity;
    size_t n_items;
} owl_queue_t;

//

owl_queue_t *owl_queue_init(size_t el_size, size_t capacity, void (*el_free)(void *data))
{
    owl_queue_t *queue = malloc(sizeof(owl_queue_t));
    queue->_internal_list = owl_sll_init(el_size, el_free);
    queue->el_size = el_size;
    queue->max_capacity = capacity;
    queue->n_items = 0;
    return queue;
}

void owl_queue_free(owl_queue_t *queue)
{
    owl_sll_free(queue->_internal_list);
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

void owl_queue_print(owl_queue_t *queue, void (*format)(void *data), char *connection_sym)
{
    if (!owl_sll_length(queue->_internal_list))
    {
        printf("EMPTY\n");
        return;
    }

    owl_sll_node_t *cursor = owl_sll_head(queue->_internal_list);
    char *conn_sym = connection_sym ? connection_sym : "|";

    printf("%s ", conn_sym);

    while (cursor)
    {
        format(cursor->data);
        printf(" %s ", conn_sym);
        cursor = cursor->next;
    }

    printf("\n");
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

size_t owl_queue_max_capacity(owl_queue_t *queue)
{
    return queue->max_capacity;
}

size_t owl_queue_n_items(owl_queue_t *queue)
{
    return queue->n_items;
}
