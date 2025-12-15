#ifndef QUESTION1_H
#define QUESTION1_H

#include <unistd.h>

static inline void print_welcome_message() {
    write(STDOUT_FILENO, "\nWelcome to ENSEA Shell.\n", 25);
    write(STDOUT_FILENO, "To exit, type 'exit'.\n", 22);
    write(STDOUT_FILENO, "enseash % ", 10);
}

#endif