#ifndef PIPE_H
#define PIPE_H


int has_pipe(char *commande);

void execute_pipe(char *commande, int *status);

#endif
