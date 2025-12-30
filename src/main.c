#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "builtins.h"
#include "executor.h"
#include "signals.h"
#include "pipe.h"

#define MAX_LINE 1024
#define MAX_ARGS 64

int main() {
    char input[MAX_LINE];
    char *args[MAX_ARGS];

    setup_shell_signals();

    while (1) {
        printf("mini-shell> ");
        fflush(stdout);

        if (!fgets(input, MAX_LINE, stdin)) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;
        if (strlen(input) == 0) continue;

        parse_input(input, args);

        int b = handle_builtin(args);
        if (b == -1) break;
        if (b == 1) continue;

        if (handle_pipe(args)) continue;

        execute_command(args);
    }

    return 0;
}
