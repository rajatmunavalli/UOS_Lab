/*Write the program to use fork/ vfork system call. Justify the difference by using suitable application of fork/vfork system calls. */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>
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
        printf("\nChild process: PID=%d, PPID=%d\n", getpid(), getppid());
        printFibonacci(10);
    }
    else
    {
        // Parent process
        printf("\nParent process: PID=%d, Child PID=%d\n", getpid(), pid);
    }

    return 0;
}
