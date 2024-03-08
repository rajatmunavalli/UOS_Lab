#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h> //defines scheduling parameter structure

int main()
{
    /* fork() creates a new process by duplicating the calling process.
       The new process is referred to as the child process.  The calling
       process is referred to as the parent process.*/

    printf("PID Parent Process: %d\n", getpid());
    pid_t pid = fork(); // pid_t signed integer type which is capable of representing a process ID

    if (pid == 0)
    {
        // Child process
        char *programPath = "/home/rajat/SEM_6/UOS_Lab/e";
        char *programArgs[] = {programPath, NULL};
        execvp(programPath, programArgs); // execute with path
        // If exec fails
        perror("Error in execvp");
    }
    else if (pid > 0)
    {
        // Parent process
        printf("Parent process continues...\n");
    }
    else
    {
        // Fork failed
        perror("Error in fork");
    }

    return 0;
}