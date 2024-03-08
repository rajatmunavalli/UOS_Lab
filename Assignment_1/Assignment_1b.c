/*Write the application or program to create Childs assign the task to them by variation exec system calls. */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *programPath = "/home/rajat/Desktop/SEM 6/UOS_Lab/a.out";
    char *programArgs[] = {programPath, NULL};
    execvp(programPath, programArgs); // execute with path
    return 0;
}