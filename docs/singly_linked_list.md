# sll.c

[Singly Linked List](https://en.wikipedia.org/wiki/Linked_list) implmentation in c.

## Example

```c
#include <stdio.h>
#include "data_structure/singly_linked_list.h"

typedef struct
{
    int id;
    char* name;
} data_t;

// The format function to print the data.
void format(void* data) {
    data_t* casted_data = (data_t*)data;
    printf("{ %d, %s }", casted_data->id, casted_data->name);
}

int main(int argc, const char* argv[]) {
    data_t data = {1, "Alice"};
    data_t data2 = {2, "Bob"};

    // create a new list where each item is a `data_t`. The first
    // argument is the size of the data.
    owl_sll_t* list = owl_sll_init(sizeof(data_t));

    // Here we'll load some data into the list. Insert operations performs a copy of the data.
    owl_sll_finsert(list, &data);
    owl_sll_finsert(list, &data2);

    // Print function takes in a custom format function that will
    // print the data. The last argument is a optional symbol that
    // will be used to represent connection between two nodes.
    owl_sll_print(list, format, "-");
    data_t *data = owl_sll_fremove(list);
    printf("length: %lu\n", owl_sll_length(list));

    // deallocate resources
    owl_sll_destroy(list);
}

/* Ouput
{ 2, Bob } - { 1, Alice } - END
length: 1
*/

```

## Functions

### Basics

```sh
owl_sll_init     # allocate a new linked list
owl_sll_destroy  # free the linked list
owl_sll_finsert  # forward insert a new node
owl_sll_binsert  # backward insert a new node
owl_sll_fremove  # remove and return a node's data from forward
owl_sll_bremove  # remove and return a node's data from backward
owl_sll_print    # print the list
```

### Getters

```sh
owl_sll_head     # get a pointer to the head
owl_sll_tail     # get a pointer to the tail
owl_sll_length   # get the current length
```

## API

```c
owl_sll_t *owl_sll_init(size_t size); // return an opaque handle to the linked list. The first argument is the size of the data.
void owl_sll_destroy(owl_sll_t *list);
void owl_sll_binsert(owl_sll_t *list, void *data);
void *owl_sll_bremove(owl_sll_t *list);
void owl_sll_finsert(owl_sll_t *list, void *data);
void *owl_sll_fremove(owl_sll_t *list);
void owl_sll_print(owl_sll_t *list, void (*format)(void *data), void *connector_symbol); // The last argument should be a char *

// Getters
owl_sll_node_t *owl_sll_head(owl_sll_t *list);
owl_sll_node_t *owl_sll_tail(owl_sll_t *list);
unsigned long int owl_sll_length(owl_sll_t *list);
```
