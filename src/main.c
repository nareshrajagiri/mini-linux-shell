#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include<signal.h>

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
