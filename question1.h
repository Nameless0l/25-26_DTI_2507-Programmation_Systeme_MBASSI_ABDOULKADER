#ifndef QUESTION1_H
#define QUESTION1_H

#include <unistd.h>

static inline void print_welcome_message() {
    write(STDOUT_FILENO, "\nBienvenue dans le Shell ENSEA.\n", 32);
    write(STDOUT_FILENO, "Pour quitter, tapez 'exit'.\n", 28);
    write(STDOUT_FILENO, "enseash % ", 10);
}

#endif