<div align="center">

# cli.h
A small header-only library for writing simple CLI tools.

</div>

## Usage

```c
#include <stdio.h>

#define CLI_IMPLEMENTATION
#include "cli.h"

void cmd_hello(int argc, char **argv) {
    printf("hello, world!\n");
}

int main(int argc, char **argv) {
    cli_cmd_t *hello = cli_add_cmd("hello", cmd_hello);
    // A description is not required.
    hello->description = "Prints \"Hello, world!\" to the console";
    
    cli_cmd_handler_t cmd_handler = NULL;
    if (argc < 2) {
        cli_print_usage(argc, argv);
        return 1;
    }

    cmd_handler = cli_get_cmd_handler(argv[1]);
    if (cmd_handler == NULL) {
        printf("Unknown command: %s\n", argv[1]);
        return 1;
    }

    cmd_handler(argc - 2, argv + 2);
    
    return 0;
}
```