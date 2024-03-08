#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <receiver_pid>\n", argv[0]);
        return 1;
    }

    pid_t receiver_pid = atoi(argv[1]);

    printf("Sender process is running with PID: %d\n", getpid());

    printf("Sending signal to receiver (PID: %d)...\n", receiver_pid);
    if (kill(receiver_pid, SIGUSR1) == -1)
    {
        perror("Error sending signal");
        return 1;
    }

    printf("Signal sent successfully.\n");

    return 0;
}
