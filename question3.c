#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
# include "question1.h"
# include "constantes.h"

int main() {
    // 1. Affichage

    print_welcome_message();
    // 2. Exécution
    char commande[TAILLE_MAX_COMMANDE];
    ssize_t taille_commande;

    
    while (1)
    {
        write(1, "enseash % ", 11);
        taille_commande = read(0, commande, TAILLE_MAX_COMMANDE - 1);
        if (taille_commande<0)
        {
            perror("Erreur lors de la lecture de la commande");
            break;
        }
        commande[taille_commande - 1] = '\0';
        if (strcmp(commande, "exit") == 0)
        {
            write(1, "Bye Bye\n", 8);
            break;
        }
        if (taille_commande == 0)
        {
            write(1, "Bye Bye\n", 8);
            break;
        }
        // Exécution de la commande
        pid_t pid = fork();
        if (pid ==-1)
        {
            perror("Erreur lors de la creation du terminal");
            continue;
        }
        if(pid == 0){
            execlp(commande, commande, NULL);
        }else
        {
            wait(NULL);
        }

    }

    return 0;
}