#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<signal.h>
#include<fcntl.h>


#define MAX_LINE 1024
#define MAX_ARGS 64

void parse_input(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " ");

    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
}

int main() {
    char input[MAX_LINE];
    char *args[MAX_ARGS];
    signal(SIGINT, SIG_IGN);


    while (1) {
        printf("mini-shell> ");
        fflush(stdout);

        if (fgets(input, MAX_LINE, stdin) == NULL) {
            printf("\n");
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
            continue;

        parse_input(input, args);
        int pipe_index = -1;

        for (int i = 0; args[i] != NULL; i++) 
        {
        
            if (strcmp(args[i], "|") == 0) 
            {
             pipe_index = i;
             args[i] = NULL;   // split command
             break;
            }
        }


        int background = 0;

        for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "&") == 0) {
        background = 1;
        args[i] = NULL;   // 🚨 remove '&' from argv
        break;
    }
}


        /* ---- BUILT-IN COMMANDS (MUST BE BEFORE fork) ---- */
        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else if (chdir(args[1]) != 0) {
                perror("cd failed");
            }
            continue;   //  VERY IMPORTANT
        }


        /* -------------------------------------------------- */

        /* ---------- PIPE HANDLING ---------- */
if (pipe_index != -1) {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        continue;
    }

    pid_t p1 = fork();
    if (p1 == 0) {
        // First command: cmd1 | ...
        signal(SIGINT, SIG_DFL);
        dup2(pipefd[1], STDOUT_FILENO);  // stdout → pipe write
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(args[0], args);
        perror("exec failed");
        exit(1);
    }

    pid_t p2 = fork();
    if (p2 == 0) {
        // Second command: ... | cmd2
        signal(SIGINT, SIG_DFL);
        dup2(pipefd[0], STDIN_FILENO);   // stdin ← pipe read
        close(pipefd[1]);
        close(pipefd[0]);
        execvp(args[pipe_index + 1], &args[pipe_index + 1]);
        perror("exec failed");
        exit(1);
    }

    // Parent
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(p1, NULL, 0);
    waitpid(p2, NULL, 0);
    continue;   // 🚨 skip normal fork
}
/* ---------------------------------- */


        pid_t pid = fork();
       if (pid == 0) {
	 signal(SIGINT, SIG_DFL);   // child should die on Ctrl+C
 	 execvp(args[0], args);
    	 perror("exec failed");
   	 exit(EXIT_FAILURE);
       }

        else if (pid > 0) {
            if (!background) {
    waitpid(pid, NULL, 0);
} else {
    printf("[background pid %d]\n", pid);
}

        } 
        else {
            perror("fork failed");
        }
    }

    return 0;
}
