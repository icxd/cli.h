#ifndef __CLI_H
#define __CLI_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*cli_cmd_handler_t)(int argc, char *argv[]);
typedef struct cli_cmd_t {
    const char *name;
    const char *description;
    cli_cmd_handler_t handler;
} cli_cmd_t;

void cli_print_usage(int argc, char *argv[]);
cli_cmd_t *cli_add_cmd(const char *name, cli_cmd_handler_t handler);
cli_cmd_handler_t cli_get_cmd_handler(const char *name);

#ifdef __cplusplus
}
#endif

#ifdef CLI_IMPLEMENTATION

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static cli_cmd_t *cli_cmds = NULL;
static int cli_cmds_count = 0;

void cli_print_usage(int argc, char *argv[]) {
    int i = 0;

    printf("Usage: %s [<args>]\n", argv[0]);
    printf("\n");
    printf("Available commands:\n");
    for (i = 0; i < cli_cmds_count; i++) {
        int text_length = strlen(cli_cmds[i].name);
        int padding = 20 - text_length;
        printf("  %s", cli_cmds[i].name);
        for (int i = 0; i < padding; i++) {
            printf(" ");
        }

        if (cli_cmds[i].description != NULL) {
            printf(" %s", cli_cmds[i].description);
        }
        printf("\n");
    }
}

cli_cmd_t *cli_add_cmd(const char *name, cli_cmd_handler_t handler) {
    cli_cmd_t *cmd = NULL;

    cmd = (cli_cmd_t *)realloc(cli_cmds, sizeof(cli_cmd_t) * (cli_cmds_count + 1));
    if (cmd == NULL) {
        return NULL;
    }

    cli_cmds = cmd;
    cmd = cli_cmds + cli_cmds_count;
    cmd->name = name;
    cmd->description = NULL;
    cmd->handler = handler;

    cli_cmds_count++;
    
    return cmd;
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

#ifdef __cplusplus
}
#endif

#endif // CLI_IMPLEMENTATION

#endif // __CLI_H