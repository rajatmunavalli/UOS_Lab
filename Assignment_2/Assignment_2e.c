#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

void sighup(int);
void sigint(int);
void sigquit(int);
void sig_handler(int);

int main() {
    int pid;

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        struct sigaction sa;

        sa.sa_handler = sighup;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        sigaction(SIGHUP, &sa, NULL);

        sa.sa_handler = sigint;
        sigaction(SIGINT, &sa, NULL);

        sa.sa_handler = sigquit;
        sigaction(SIGQUIT, &sa, NULL);

        sa.sa_handler = sig_handler;
        sigaction(SIGUSR1, &sa, NULL);
        sigaction(SIGSTOP, &sa, NULL);

        for (;;);
    } else {
        printf("\nPARENT: sending SIGHUP\n\n");
        kill(pid, SIGHUP);
        sleep(3);

        printf("\nPARENT: sending SIGINT\n\n");
        kill(pid, SIGINT);
        sleep(3);

        printf("\nPARENT: sending SIGQUIT\n\n");
        kill(pid, SIGQUIT);
        sleep(3);

        printf("\nPARENT: sending SIGUSR1\n\n");
        kill(pid, SIGUSR1);
        sleep(3);

        printf("\nPARENT: sending SIGSTOP\n\n");
        kill(pid, SIGSTOP);
        sleep(3);
    }
    return 0;
}

void sighup(int signo) {
    printf("CHILD: I have received a SIGHUP\n");
}

void sigint(int signo) {
    printf("CHILD: I have received a SIGINT\n");
}

void sigquit(int signo) {
    printf("My DADDY has Killed me!!!\n");
    exit(0);
}

void sig_handler(int signo) {
    if (signo == SIGUSR1) {
        printf("received SIGUSR1\n");
    } else if (signo == SIGSTOP) {
        printf("received SIGSTOP\n");
    }
}
