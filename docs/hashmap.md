# hashmap.c

[Hashmap](https://en.wikipedia.org/wiki/Hash_table) implementation based on Open addressing using Robin Hood hashing in c.

## Example

```c
#include "owl.h"
#include <stdio.h>
#include <string.h>

struct user
{
    char *name;
    int age;
};

int user_compare(const void *a, const void *b, void *udata)
{
    const struct user *ua = a;
    const struct user *ub = b;
    return strcmp(ua->name, ub->name);
}

bool user_iter(const void *item, void *udata)
{
    const struct user *user = item;
    printf("%s (age=%d)\n", user->name, user->age);
    return true;
}

uint64_t user_hash(const void *item, uint64_t seed0, uint64_t seed1)
{
    const struct user *user = item;
    return owl_hashmap_sip(user->name, strlen(user->name), seed0, seed1);
}

int main(int argc, const char *argv[])
{
    struct hashmap *map = owl_hashmap_new(sizeof(struct user), 0, 0, 0,
                                          user_hash, user_compare, NULL, NULL);

    owl_hashmap_set(map, &(struct user){.name = "Dale", .age = 44});
    owl_hashmap_set(map, &(struct user){.name = "Roger", .age = 68});
    owl_hashmap_set(map, &(struct user){.name = "Jane", .age = 47});

    struct user *user;

    printf("\n-- get some users --\n");
    user = owl_hashmap_get(map, &(struct user){.name = "Jane"});
    printf("%s age=%d\n", user->name, user->age);

    user = owl_hashmap_get(map, &(struct user){.name = "Roger"});
    printf("%s age=%d\n", user->name, user->age);

    user = owl_hashmap_get(map, &(struct user){.name = "Dale"});
    printf("%s age=%d\n", user->name, user->age);

    user = owl_hashmap_get(map, &(struct user){.name = "Tom"});
    printf("%s\n", user ? "exists" : "not exists");

    printf("\n-- iterate over all users (hashmap_scan) --\n");
    owl_hashmap_scan(map, user_iter, NULL);

    printf("\n-- iterate over all users (hashmap_iter) --\n");
    size_t iter = 0;
    void *item;
    while (owl_hashmap_iter(map, &iter, &item))
    {
        const struct user *user = item;
        printf("%s (age=%d)\n", user->name, user->age);
    }

    owl_hashmap_free(map);
}

/* Ouput
-- get some users --
Jane age=47
Roger age=68
Dale age=44
not exists

-- iterate over all users (hashmap_scan) --
Dale (age=44)
Roger (age=68)
Jane (age=47)

-- iterate over all users (hashmap_iter) --
Dale (age=44)
Roger (age=68)
Jane (age=47)
*/

```

## Functions

### Basics

```sh
owl_hashmap_new                  # allocate a new hashmap
owl_hashmap_new_with_allocator   # allocate a new hashmap with custom allocators
owl_hashmap_free                 # deallocate the hashmap
owl_hashmap_get                  # get an existing item
owl_hashmap_set                  # insert or replace an existing item and return the previous
owl_hashmap_delete               # delete and return an item
owl_hashmap_clear                # clear the hash map
```

### Getters

```sh
owl_hashmap_count                # get the number of items in the hash map
owl_hashmap_oom                  # check if the machine is out-of-memory
```

### Helpers

```sh
owl_hashmap_sip                  # returns hash value for data using SipHash-2-4
owl_hashmap_murmur               # returns hash value for data using MurmurHash3
```

## API

```c
owl_hashmap_t *owl_hashmap_new(size_t elsize, size_t cap,
                               uint64_t seed0, uint64_t seed1,
                               uint64_t (*hash)(const void *item,
                                                uint64_t seed0, uint64_t seed1),
                               int (*compare)(const void *a, const void *b,
                                              void *udata),
                               void (*elfree)(void *item),
                               void *udata);

owl_hashmap_t *owl_hashmap_new_with_allocator(
    void *(*malloc)(size_t),
    void *(*realloc)(void *, size_t),
    void (*free)(void *),
    size_t elsize, size_t cap,
    uint64_t seed0, uint64_t seed1,
    uint64_t (*hash)(const void *item,
                     uint64_t seed0, uint64_t seed1),
    int (*compare)(const void *a, const void *b,
                   void *udata),
    void (*elfree)(void *item),
    void *udata);

void owl_hashmap_free(owl_hashmap_t *map);
void owl_hashmap_clear(owl_hashmap_t *map, bool update_cap);
void *owl_hashmap_get(owl_hashmap_t *map, const void *item);
void *owl_hashmap_set(owl_hashmap_t *map, const void *item);
void *owl_hashmap_delete(owl_hashmap_t *map, void *item);
bool owl_hashmap_scan(owl_hashmap_t *map,
                      bool (*iter)(const void *item, void *udata), void *udata);
bool owl_hashmap_iter(owl_hashmap_t *map, size_t *i, void **item);

// Getters
size_t owl_hashmap_count(owl_hashmap_t *map);
bool owl_hashmap_oom(owl_hashmap_t *map);

// Helpers
uint64_t owl_hashmap_sip(const void *data, size_t len,
                         uint64_t seed0, uint64_t seed1);
uint64_t owl_hashmap_murmur(const void *data, size_t len,
                            uint64_t seed0, uint64_t seed1);
```

### Note

This implementation is a wrapper over [tidwall/hashmap.c](https://github.com/tidwall/hashmap.c). I plan to rewrite the implementation in the future.
