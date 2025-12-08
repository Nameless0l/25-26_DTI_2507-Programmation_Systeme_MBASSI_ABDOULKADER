#include<stdio.h>
#include <unistd.h>


int main() {
    // Affichage d’un message d’accueil, suivi d’un prompt simple. Par exemple :
    // $ ./enseash
    // Bienvenue dans le Shell ENSEA.
    // Pour quitter, tapez 'exit'.
    // enseash %


    write(1, "\nBienvenue dans le Shell ENSEA.\n", 30);
    write(1, "\nPour quitter, tapez 'exit'.\n", 29);
    write(1, "enseash % \n", 11);


    return 0;
}