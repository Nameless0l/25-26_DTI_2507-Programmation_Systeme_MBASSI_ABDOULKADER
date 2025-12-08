#ifndef QUESTION2_H
#define QUESTION2_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * Display the shell prompt
 */
void display_prompt() {
    write(STDOUT_FILENO, "enseash % ", 10);
}

/**
 * Read a command from standard input
 * Returns: number of bytes read, or -1 on error/EOF
 */
ssize_t read_command(char *command, size_t max_size) {
    ssize_t bytes_read = read(STDIN_FILENO, command, max_size - 1);
    
    if (bytes_read <= 0) {
        return bytes_read;
    }
    
    // Replace newline with null terminator
    command[bytes_read - 1] = '\0';
    
    return bytes_read;
}

/**
 * Check if the command is 'exit'
 * Returns: 1 if exit command, 0 otherwise
 */
int is_exit_command(const char *command) {
    return strcmp(command, "exit") == 0;
}

/**
 * Execute a simple command (without arguments)
 * Returns: 0 on success, -1 on error
 */
int execute_command(const char *command) {
    pid_t pid = fork();
    
    if (pid == -1) {
        // Fork failed
        write(STDERR_FILENO, "Error: fork failed\n", 19);
        return -1;
    }
    
    if (pid == 0) {
        // Child process: execute the command
        execlp(command, command, NULL);
        
        // If execlp returns, it failed
        write(STDERR_FILENO, "Error: command not found\n", 25);
        _exit(1);
    }
    else {
        // Parent process: wait for child to finish
        int status;
        waitpid(pid, &status, 0);
    }
    
    return 0;
}

#endif // QUESTION2_H
