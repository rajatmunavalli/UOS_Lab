#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Receiver process received signal SIGUSR1. Terminating...\n");
        exit(EXIT_SUCCESS);
    }
}

int main() {
    printf("Receiver process is running with PID: %d\n", getpid());

    signal(SIGUSR1, signal_handler);

    printf("Receiver process is waiting for signals...\n");

    while (1) {
        sleep(1); // Keep the receiver process running
    }

    return 0;
}
