//
//  linked_list.h
//  libowl
//
//  Created by Rahul Gupta on 27/09/22.
//

#ifndef linked_list_h
#define linked_list_h

#include <stdlib.h>

typedef struct Node
{
    unsigned int id;
    void *data;
    struct Node* next;
} owl_sll_node_t;

typedef struct SinglyLinkedList owl_sll_t;

owl_sll_t *owl_sll_init(size_t size);
void owl_sll_destroy(owl_sll_t *list);
void owl_sll_binsert(owl_sll_t *list, void *data);
void *owl_sll_bremove(owl_sll_t *list);
void owl_sll_finsert(owl_sll_t *list, void *data);
void *owl_sll_fremove(owl_sll_t *list);
void owl_sll_print(owl_sll_t *list, void (*format)(void *data), void *connector_symbol);

// Getters

owl_sll_node_t *owl_sll_head(owl_sll_t *list);
owl_sll_node_t *owl_sll_tail(owl_sll_t *list);
unsigned long int owl_sll_length(owl_sll_t *list);

#endif /* linked_list_h */
