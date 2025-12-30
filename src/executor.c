#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include "executor.h"
#include "signals.h"

void execute_command(char **args) {
    int background = 0;

    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], "&") == 0) {
            background = 1;
            args[i] = NULL;
            break;
        }
    }

    pid_t pid = fork();
    if (pid == 0) {
        setup_child_signals();
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    }

    if (!background) {
        waitpid(pid, NULL, 0);
    } else {
        printf("[background pid %d]\n", pid);
    }
}
