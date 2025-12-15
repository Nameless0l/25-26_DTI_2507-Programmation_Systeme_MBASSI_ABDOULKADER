#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "command.h"

void parse_command(char *commande, char **args) {
    int i = 0;
    char *token = strtok(commande, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL; 
}

void handle_redirection(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], ">") == 0) {
            args[i] = NULL; 
            int fd = open(args[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd < 0) {
                perror("Error opening redirection file");
                _exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;
        } else if (strcmp(args[i], "<") == 0) {
            args[i] = NULL; 
            int fd = open(args[i + 1], O_RDONLY);
            if (fd < 0) {
                perror("Error opening redirection file");
                _exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            break;
        }
    }
}
