#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "builtins.h"

int handle_builtin(char **args) {
    if (!args[0]) return 1;

    if (strcmp(args[0], "exit") == 0) {
        return -1;  // signal shell to exit
    }

    if (strcmp(args[0], "cd") == 0) {
        if (!args[1]) {
            fprintf(stderr, "cd: missing argument\n");
        } else if (chdir(args[1]) != 0) {
            perror("cd failed");
        }
        return 1;
    }

    return 0;
}
