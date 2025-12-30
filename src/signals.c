#include <signal.h>
#include <sys/wait.h>
#include <stddef.h> 

#include "signals.h"

static void handle_sigchld(int sig) {
    (void)sig;
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void setup_shell_signals(void) {
    signal(SIGINT, SIG_IGN);
    signal(SIGCHLD, handle_sigchld);
}

void setup_child_signals(void) {
    signal(SIGINT, SIG_DFL);
}
