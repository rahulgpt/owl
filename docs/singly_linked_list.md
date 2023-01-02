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
    data_t* d = data;
    printf("{ %d, %s }", d->id, d->name);
}

int main(int argc, const char* argv[]) {
    // create a new list where each item is a `data_t`. The first
    // argument is the size of the data and the second argument is
    // a custom free function.
    owl_sll_t* list = owl_sll_init(sizeof(data_t), NULL);

    // Here we'll load some data into the list. Insert operations performs a copy of the data.
    owl_sll_finsert(list, &(data_t){ .id=1, .name="Alice" });
    owl_sll_finsert(list, &(data_t){ .id=2, .name="Bob" });

    // Print function takes in a custom format function that will
    // print the data. The last argument is a optional symbol that
    // will be used to represent connection between two nodes.
    owl_sll_print(list, format, "-");

    // returns the pointer to the data on the heap.
    data_t *data = owl_sll_fremove(list);

    // free the data when we are done.
    free(data);

    printf("length: %zu\n", owl_sll_length(list));

    // deallocate resources
    owl_sll_free(list);
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
owl_sll_free     # free the linked list
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
owl_sll_t *owl_sll_init(size_t size, void (*elfree)(void *data)); // return a handle to the list.
void owl_sll_free(owl_sll_t *list);
void owl_sll_binsert(owl_sll_t *list, void *data);
void *owl_sll_bremove(owl_sll_t *list);
void owl_sll_finsert(owl_sll_t *list, void *data);
void *owl_sll_fremove(owl_sll_t *list);
void owl_sll_print(owl_sll_t *list, void (*format)(void *data), char *connection_sym);

// Getters
owl_sll_node_t *owl_sll_head(owl_sll_t *list);
owl_sll_node_t *owl_sll_tail(owl_sll_t *list);
size_t owl_sll_length(owl_sll_t *list);
```
