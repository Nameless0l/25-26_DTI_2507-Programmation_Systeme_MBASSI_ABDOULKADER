#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
# include "question1.h"
# include "constantes.h"

int main() {
    // 1. Affichage d’un message d’accueil, suivi d’un prompt simple. Par exemple :

    print_welcome_message();
    // 2. Exécution de la commande saisie et retour au prompt (REPL : read–eval–print loop) :
    char commande[TAILLE_MAX_COMMANDE];
    ssize_t taille_commande;
    
    while (1)
    {
        write(1, "enseash % ", 11);
        taille_commande = read(STDIN_FILENO, commande, TAILLE_MAX_COMMANDE - 1);
        if (taille_commande<=0)
        {
            break;
        }
        commande[taille_commande - 1] = '\0';
        if (strcmp(commande, "exit") == 0)
        {
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