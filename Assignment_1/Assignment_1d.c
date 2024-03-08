/*Write the program to use wait/ waitpid system call and explain what it do when call in parent and called in child (). Justify the difference by using
suitable application*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void printFibonacci(int n)
{
    int a = 0, b = 1, c;

    printf("Fibonacci series (up to %d terms): ", n);

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }

    printf("\n");
}

int main()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("Child process: PID=%d, PPID=%d\n", getpid(), getppid());
        printFibonacci(10);
    }
    else
    {
        // Parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), pid);

        // Using wait system call in the parent
        pid_t terminated_pid = wait(NULL);

        if (terminated_pid == -1)
        {
            perror("wait");
            return 1;
        }

        printf("Parent process: Child with PID=%d terminated\n", terminated_pid);

        // Using waitpid system call in the parent
        pid_t pid_waitpid = fork();

        if (pid_waitpid == -1)
        {
            perror("fork");
            return 1;
        }

        if (pid_waitpid == 0)
        {
            // Child process for waitpid
            printf("Child process for waitpid: PID=%d, PPID=%d\n", getpid(), getppid());
            printFibonacci(8);
        }
        else
        {
            // Parent process for waitpid
            printf("\nParent process for waitpid: PID=%d, Child PID=%d\n", getpid(), pid_waitpid);

            // Using waitpid system call in the parent without storing the status
            pid_t terminated_pid_waitpid = waitpid(pid_waitpid, NULL, 0);

            if (terminated_pid_waitpid == -1)
            {
                perror("waitpid");
                return 1;
            }

            printf("Parent process for waitpid: Child with PID=%d terminated\n", terminated_pid_waitpid);
        }
    }

    return 0;
}
