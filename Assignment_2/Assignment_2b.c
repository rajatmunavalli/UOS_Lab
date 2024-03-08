#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int x = 0;

void handle_sigusr1()
{
    if (x == 0)
        printf("\n(HINT) Multiplication is Repetitive Addition!\n");
}
int main()
{
    int pid = fork();

    if (pid == -1)
    {
        return 1;
    }
    if (pid == 0)
    {
        // Child Process
        sleep(5);
        kill(getppid(), SIGUSR1);
    }
    else
    {
        struct sigaction sa = {0};
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);
        // Parent Process
        printf("What is 3 times 5: ");
        scanf("%d", &x);
        if (x == 15)
            printf("Right!\n");
        else
            printf("Wrong!\n");
        wait(NULL);
    }
}