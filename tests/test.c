#include <stdio.h>

#define CLI_IMPLEMENTATION
#include "../cli.h"

void cmd_hello(int argc, char **argv) {
    printf("hello, world!\n");
}

int main(int argc, char **argv) {
    cli_add_cmd("hello", cmd_hello);
    
    cli_cmd_handler_t cmd_handler = NULL;
    if (argc < 2) {
        cli_print_usage();
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