#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signum)
{
    // This function will be called when the alarm signal is received
    printf("\nTime limit exceeded. Exiting...\n");
    exit(EXIT_FAILURE);
}

int main()
{
    // Set up the signal handler for the alarm signal
    signal(SIGALRM, alarm_handler);

    char buffer[256];
    printf("Enter input within 10 seconds:\n");

    // Set the alarm to 10 seconds
    alarm(10);

    // Read input from the user
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // If input is received before the alarm, cancel the alarm
        alarm(0);
        printf("Input received: %s", buffer);
    }
    else
    {
        // If fgets returns NULL, it indicates an error or EOF, handle accordingly
        printf("Error reading input.\n");
    }

    return 0;
}
