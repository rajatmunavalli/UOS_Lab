#include <stdio.h>
#include <signal.h>

void ctrlc_handler(int sig) {
    printf("\nCtrl-C trapped! But I won't quit!\n");
}

int main() {
    if (signal(SIGINT, ctrlc_handler) == SIG_ERR) {
        perror("Error registering signal handler");
        return 1;
    }

    printf("Running... Press Ctrl-C to trap the signal.\n");

    for (int i = 1; i <= 10; ++i) {
        printf("%d\n", i);
    }

    while(1) {
    }

    return 0;
}
