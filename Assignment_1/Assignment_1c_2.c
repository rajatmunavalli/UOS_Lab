/*Write the program to use fork/ vfork system call. Justify the difference by using suitable application of fork/vfork system calls. */

#include <stdio.h>
#include <unistd.h>
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
    pid_t pid = vfork();

    if (pid == -1)
    {
        perror("vfork");
        return 1;
    }

    if (pid == 0)
    {
        // Child process
        printf("\nChild process (vfork): PID=%d, PPID=%d\n", getpid(), getppid());
        printFibonacci(10);
        _exit(0); 
    }
    else
    {
        // Parent process
        printf("\nParent process (vfork): PID=%d, Child PID=%d\n", getpid(), pid);
    }

    return 0;
}
