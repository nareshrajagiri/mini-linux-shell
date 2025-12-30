#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>


#include "pipe.h"
#include "signals.h"

int handle_pipe(char **args) {
    int idx = -1;

    for (int i = 0; args[i]; i++) {
        if (strcmp(args[i], "|") == 0) {
            idx = i;
            args[i] = NULL;
            break;
        }
    }

    if (idx == -1) return 0;

    int pipefd[2];
    pipe(pipefd);

    pid_t p1 = fork();
    if (p1 == 0) {
        setup_child_signals();
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]); close(pipefd[1]);
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    }

    pid_t p2 = fork();
    if (p2 == 0) {
        setup_child_signals();
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]); close(pipefd[1]);
        execvp(args[idx + 1], &args[idx + 1]);
        perror("exec failed");
        exit(1);
    }

    close(pipefd[0]); close(pipefd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);

    return 1;
}
