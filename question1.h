#include <unistd.h>

void afficher_message_accueil() {
    write(1, "\nBienvenue dans le Shell ENSEA.\n", 30);
    write(1, "\nPour quitter, tapez 'exit'.\n", 29);
    write(1, "enseash % ", 11);
}