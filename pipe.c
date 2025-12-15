#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include "pipe.h"
#include "command.h"
#include "constants.h"

int has_pipe(char *commande) {
    return strchr(commande, '|') != NULL;
}

void execute_pipe(char *commande, int *status) {
    char *cmd1, *cmd2;
    char *args1[MAX_ARGS];
    char *args2[MAX_ARGS];
    int pipefd[2];
    
    cmd1 = strtok(commande, "|");
    cmd2 = strtok(NULL, "|");
    
    if (cmd1 == NULL || cmd2 == NULL) {
        write(2, "Pipe error: invalid syntax\n", 27);
        return;
    }
    
    // Remove leading spaces
    while (*cmd1 == ' ') cmd1++;
    while (*cmd2 == ' ') cmd2++;
    
    if (pipe(pipefd) == -1) {
        perror("Pipe creation failed");
        return;
    }
    
    // First child: executes cmd1, output goes to pipe
    pid_t pid1 = fork();
    if (pid1 == -1) {
        perror("Fork failed");
        return;
    }
    
    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        
        parse_command(cmd1, args1);
        handle_redirection(args1);
        execvp(args1[0], args1);
        write(2, "Command not found\n", 18);
        _exit(1);
    }
    
    pid_t pid2 = fork();
    if (pid2 == -1) {
        perror("Fork failed");
        return;
    }
    
    if (pid2 == 0) {
        // Child 2: redirect stdin to pipe read
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        
        parse_command(cmd2, args2);
        handle_redirection(args2);
        execvp(args2[0], args2);
        write(2, "Command not found\n", 18);
        _exit(1);
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, status, 0);
}