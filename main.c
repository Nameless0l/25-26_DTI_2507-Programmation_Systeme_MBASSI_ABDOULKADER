#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>

// custom includes
# include "question1.h"
# include "constantes.h"
#define BILLION  1000000000L;

int main() {
    // 1. Affichage

    print_welcome_message();
    // 2. Exécution
    char commande[TAILLE_MAX_COMMANDE];
    ssize_t taille_commande;
    struct timespec start, finish;

    int status;
    bool display_status = false;
    
    
    while (1)
    {
        if(!display_status){
            // write(1, "enseash % ", 11);
        }else if (WIFEXITED(status)) {
            write(1, "enseash [exit:", 14);
            int exit_code = WEXITSTATUS(status);
            char code_str[10];
            int len = 0;
            if (exit_code == 0) {
                code_str[len++] = '0';
            } else {
                int temp = exit_code;
                int divisor = 1;
                while (temp / divisor >= 10) divisor *= 10;
                while (divisor > 0) {
                    code_str[len++] = '0' + (temp / divisor);
                    temp %= divisor;
                    divisor /= 10;
                }
            }
            write(1, code_str, len);
            write(1, "] % ", 4);
        }
        else if (WIFSIGNALED(status)) {
            write(1, "enseash [sign:", 14);
            int sig_num = WTERMSIG(status);
            char sig_str[10];
            int len = 0;
            if (sig_num == 0) {
                sig_str[len++] = '0';
            } else {
                int temp = sig_num;
                int divisor = 1;
                while (temp / divisor >= 10) divisor *= 10;
                while (divisor > 0) {
                    sig_str[len++] = '0' + (temp / divisor);
                    temp %= divisor;
                    divisor /= 10;
                }
            }
            write(1, sig_str, len);
            write(1, "] % ", 4);
        }
        
        
        taille_commande = read(STDIN_FILENO, commande, TAILLE_MAX_COMMANDE - 1);
        if (taille_commande<0)
        {
            perror("Erreur lors de la lecture de la commande");
            break;
        }
        commande[taille_commande - 1] = '\0';
        if (strcmp(commande, "exit") == 0)
        {
            write(1, "Bye Bye\n", 8);
            exit(0);
        }
        if (taille_commande == 0)
        {
            write(1, "Bye Bye\n", 8);
            exit(0);
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
            waitpid(pid, &status, 0);
            display_status = true;
        }

        time_t tv_sec;
        double accum = ( finish.tv_sec - start.tv_sec )
          + ( finish.tv_nsec - start.tv_nsec ) / BILLION;
        printf( "%lf\n", accum );
    }
    
    return 0;
}