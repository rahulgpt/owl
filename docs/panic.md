# panic.h

## Example

```c
#include <stdio.h>
#include "owl.h"

int main(int argc, const char* argv[]) {
  // This will print the error message along with the
  // file name and line number and exit the prog with
  // status code "1"
  owl_panic("Some error occured");
}
```

## Functions

```sh
owl_panic       # print error and exit the prog
```

## API

```c
#define owl_panic(_msg_)
```
