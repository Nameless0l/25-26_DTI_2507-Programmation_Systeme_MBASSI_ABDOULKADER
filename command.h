#ifndef COMMAND_H
#define COMMAND_H

#include "constantes.h"

// Parse command string into arguments array
void parse_command(char *commande, char **args);

// Handle input/output redirections (< and >)
void handle_redirection(char **args);

#endif
