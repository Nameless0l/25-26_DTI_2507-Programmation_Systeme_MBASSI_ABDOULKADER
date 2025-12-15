#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "question1.h"
#include "constants.h"

int main() {
    // 1. Display a welcome message, followed by a simple prompt. Example:

    print_welcome_message();
    // 2. Execute the entered command and return to prompt (REPL: read-eval-print loop):
    char command[MAX_COMMAND_SIZE];
    ssize_t command_size;
    
    while (1)
    {
        command_size = read(STDIN_FILENO, command, MAX_COMMAND_SIZE - 1);
        if (command_size<=0)
        {
            break;
        }
        command[command_size - 1] = '\0';
        // Check for 'exit' command
        if (strcmp(command, "exit") == 0)
        {

            exit(0);
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
        write(1, "enseash % ", 11);
        

    }
    
    return 0;
}
