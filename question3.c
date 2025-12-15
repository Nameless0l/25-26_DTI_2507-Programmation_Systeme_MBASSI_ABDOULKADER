#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
# include "question1.h"
# include "constants.h"

int main() {
    // 1. Display

    print_welcome_message();
    // 2. Execution
    char command[MAX_COMMAND_SIZE];
    ssize_t command_size;

    
    while (1)
    {
        write(1, "enseash % ", 11);
        command_size = read(0, command, MAX_COMMAND_SIZE - 1);
        if (command_size<0)
        {
            perror("Error reading command");
            break;
        }
        command[command_size - 1] = '\0';
        if (strcmp(command, "exit") == 0)
        {
            write(1, "Bye Bye\n", 8);
            break;
        }
        if (command_size == 0)
        {
            write(1, "Bye Bye\n", 8);
            break;
        }
        // Execute the command
        pid_t pid = fork();
        if (pid ==-1)
        {
            perror("Error creating child process");
            continue;
        }
        if(pid == 0){
            execlp(command, command, NULL);
        }else
        {
            wait(NULL);
        }

    }

    return 0;
}