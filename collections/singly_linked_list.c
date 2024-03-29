#include "singly_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/* Opaque type */

typedef struct __opaq_owl__sll
{
    owl_sll_node_t *head;
    owl_sll_node_t *tail;
    size_t length;
    size_t el_size;
    void (*el_free)(void *data);
} owl_sll_t;

//

owl_sll_t *owl_sll_init(size_t el_size, void (*el_free)(void *data))
{
    owl_sll_t *list = malloc(sizeof(owl_sll_t));
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
    list->el_size = el_size;
    list->el_free = el_free ? el_free : free;
    return list;
}

// This method will deallocate the linked list
// and the data.
// Todo: add custom deep free fn
void owl_sll_free(owl_sll_t *list)
{
    if (!list->length)
    {
        free(list);
        return;
    }

    owl_sll_node_t *cursor = list->head;
    owl_sll_node_t *prev = NULL;

    while (cursor)
    {
        list->el_free(cursor->data);
        prev = cursor;
        cursor = cursor->next;
        free(prev);
    }

    free(list);
}

static owl_sll_node_t *node_init(void *data, size_t el_size)
{
    static unsigned int id = 0;
    owl_sll_node_t *node = malloc(sizeof(owl_sll_node_t));
    node->data = malloc(el_size);

    // copy the content of the data
    for (int i = 0; i < el_size; i++)
        *(char *)(node->data + i) = *(char *)(data + i);

    node->next = NULL;
    node->id = id++;
    return node;
}

// free's the node without freeing the data as we want to return the
// pointer to the data. It's upto the user to free the data.
static void node_free_without_data(owl_sll_t *list, owl_sll_node_t *node)
{
    if (!node) return;
    // break any link if exist
    node->next = NULL;
    free(node);
}

void owl_sll_binsert(owl_sll_t *list, void *data)
{
    owl_sll_node_t *node = node_init(data, list->el_size);
    if (!list->head)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
    list->length++;
}

void *owl_sll_bremove(owl_sll_t *list)
{
    if (!list->length) return NULL;
    owl_sll_node_t *cursor = list->head;

    while (cursor->next && cursor->next->next)
    {
        cursor = cursor->next;
    }

    void *data = cursor->data;

    node_free_without_data(list, cursor->next);
    list->tail = cursor;
    list->tail->next = NULL;
    list->length--;

    if (list->length == 0)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    return data;
}

void owl_sll_finsert(owl_sll_t *list, void *data)
{
    owl_sll_node_t *node = node_init(data, list->el_size);
    if (!list->head)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
    list->length++;
}

void *owl_sll_fremove(owl_sll_t *list)
{
    if (!list->length) return NULL;

    void *data = list->head->data;
    owl_sll_node_t *node_to_free = list->head;

    list->head = list->head->next;
    node_free_without_data(list, node_to_free);
    list->length--;

    if (list->length == 0)
    {
        list->head = NULL;
        list->tail = NULL;
    }

    return data;
}

void owl_sll_print(owl_sll_t *list, void (*format)(void *data), char *connection_sym)
{
    if (!list->length)
    {
        printf("EMPTY\n");
        return;
    }

    owl_sll_node_t *cursor = list->head;
    char *conn_sym = connection_sym ? connection_sym : "->";

    while (cursor)
    {
        format(cursor->data);
        printf(" %s ", conn_sym);
        cursor = cursor->next;
    }

    printf("END\n");
}

// Getters

owl_sll_node_t *owl_sll_head(owl_sll_t *list)
{
    return list->head;
}

owl_sll_node_t *owl_sll_tail(owl_sll_t *list)
{
    return list->tail;
}

size_t owl_sll_length(owl_sll_t *list)
{
    return list->length;
}
