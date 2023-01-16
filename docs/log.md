# log.h

## Example

```c
#include <stdio.h>
#include "owl.h"

int main(int argc, const char* argv[]) {
  // This will print the message and change the line
  owl_println("Print this message in a line");
}
```

## Functions

```sh
owl_println       # printf with "\n" appended
```

## API

```c
#define owl_println(format, ...)
```
