#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <sys/wait.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024) // 1MB stack size

// Function to be executed by the child process
int child_function(void *arg) {
    printf("Child process: PID = %d\n", getpid());
    
    // Print 10 numbers
    for (int i = 0; i < 10; ++i) {
        printf("%d\n", i);
        sleep(0.1); 
    }
    
    return 0;
}

int main() {
    char *stack;
    pid_t pid;

    // Allocate memory for the stack
    stack = malloc(STACK_SIZE);
    if (stack == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Using clone() system call to create a child process
    pid = clone(child_function, stack + STACK_SIZE, SIGCHLD, NULL);
    if (pid == -1) {
        perror("clone");
        exit(EXIT_FAILURE);
    }

    printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);

    // Wait for the child process to terminate
    if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        exit(EXIT_FAILURE);
    }

    // Free the allocated stack memory
    free(stack);

    return 0;
}
