#define _POSIX_C_SOURCE 199309L // Include for clock_gettime(Reference: stack overflow : https://stackoverflow.com/questions/48332332/what-does-define-posix-source-mean)
#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
// custom includes
# include "question1.h"
# include "constants.h"

void write_int(long num) {
    if (num == 0) {
        write(1, "0", 1);
        return;
    }
    char buffer[20];
    int i = 0;
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}

int main() {
    print_welcome_message();
    // 2. Execution
    char command[MAX_COMMAND_SIZE];
    ssize_t command_size;
    struct timespec start_time, end_time;
    long exec_time_ms;
    int status;
    bool display_status = false;
    
    
    while (1)
    {
        if(!display_status){
            // write(1, "enseash % ", 11);
        }else if (WIFEXITED(status)) {
            write(1, "enseash [exit:", 14);
            write_int(WEXITSTATUS(status));
            write(1, "|", 1);
            write_int(exec_time_ms);
            write(1, "ms] % ", 6);
        }
        else if (WIFSIGNALED(status)) {
            write(1, "enseash [sign:", 14);
            write_int(WTERMSIG(status));
            write(1, "|", 1);
            write_int(exec_time_ms);
            write(1, "ms] % ", 6);
        }
        
        
        command_size = read(STDIN_FILENO, command, MAX_COMMAND_SIZE - 1);
        if (command_size<0)
        {
            perror("Error reading command");
            break;
        }
        command[command_size - 1] = '\0';
        if (strcmp(command, "exit") == 0)
        {
            write(1, "Bye Bye\n", 8);
            exit(0);
        }
        if (command_size == 0)
        {
            write(1, "Bye Bye\n", 8);
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
            clock_gettime(CLOCK_REALTIME, &start_time);
            waitpid(pid, &status, 0);
            clock_gettime(CLOCK_REALTIME, &end_time);
            display_status = true;
            exec_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + 
                           (end_time.tv_nsec - start_time.tv_nsec) / 1000000;
        }
    }
    
    return 0;
}