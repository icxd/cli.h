#ifndef __CLI_H
#define __CLI_H

typedef void (*cli_cmd_handler_t)(int argc, char *argv[]);
typedef struct cli_cmd_t {
    const char *name;
    cli_cmd_handler_t handler;
} cli_cmd_t;

void cli_print_usage(void);
void cli_add_cmd(const char *name, cli_cmd_handler_t handler);
cli_cmd_handler_t cli_get_cmd_handler(const char *name);

#ifdef CLI_IMPLEMENTATION

#include <string.h>
#include <stdlib.h>

static cli_cmd_t *cli_cmds = NULL;
static int cli_cmds_count = 0;

void cli_print_usage(void) {
    int i = 0;

    printf("Usage: <command> [<args>]\n");
    printf("\n");
    printf("Available commands:\n");
    for (i = 0; i < cli_cmds_count; i++) {
        printf("  %s\n", cli_cmds[i].name);
    }
}

void cli_add_cmd(const char *name, cli_cmd_handler_t handler) {
    cli_cmd_t *cmd = NULL;

    cmd = (cli_cmd_t *)realloc(cli_cmds, sizeof(cli_cmd_t) * (cli_cmds_count + 1));
    if (cmd == NULL) {
        return;
    }

    cli_cmds = cmd;
    cmd = cli_cmds + cli_cmds_count;
    cmd->name = name;
    cmd->handler = handler;

    cli_cmds_count++;
}

cli_cmd_handler_t cli_get_cmd_handler(const char *name) {
    int i = 0;

    for (i = 0; i < cli_cmds_count; i++) {
        if (strcmp(cli_cmds[i].name, name) == 0) {
            return cli_cmds[i].handler;
        }
    }

    return NULL;
}

#endif // CLI_IMPLEMENTATION

#endif // __CLI_H