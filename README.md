# Owl 🦉

A general purpose c lib.

## Docs

### collections

- [singly_linked_list](./docs/singly_linked_list.md)
- [queue](./docs/queue.md)
- [hashmap](./docs/hashmap.md)

### systems

- [thread_pool](./docs/thread_pool.md)

### utils

- [panic](./docs/panic.md)
- [log](./docs/log.md)

## Building the library

`owl` can be compiled to a static or shared library from the source by running the following commands. The library can be found at `lib/` directory.

To build the static lib

```sh
make
```

To build the shared lib

```sh
make -e SHARED=1
```

## License

owl source code is available under the MIT License.
