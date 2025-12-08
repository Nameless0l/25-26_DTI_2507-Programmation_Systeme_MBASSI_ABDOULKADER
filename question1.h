#include <unistd.h>

void print_welcome_message() {
    write(STDOUT_FILENO, "\nBienvenue dans le Shell ENSEA.\n", 30);
    write(STDOUT_FILENO, "\nPour quitter, tapez 'exit'.\n", 29);
    write(STDOUT_FILENO, "enseash % ", 11);
}