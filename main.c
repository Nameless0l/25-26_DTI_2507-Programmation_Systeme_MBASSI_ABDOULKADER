#define _POSIX_C_SOURCE 199309L // Inclut pour clock_gettime(Reference: stack overflow)
#include<stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
// custom includes
# include "question1.h"
# include "constantes.h"

int main() {
    print_welcome_message();
    // 2. Exécution
    char commande[TAILLE_MAX_COMMANDE];
    ssize_t taille_commande;
    struct timespec start_time, end_time;
    long exec_time_ms;
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
            write(1, "|", 1);
            char time_str[20];
            int time_len = 0;
            long temp_time = exec_time_ms;
            if (temp_time == 0) {
                time_str[time_len++] = '0';
            } else {
                int div = 1;
                while (temp_time / div >= 10) div *= 10;
                while (div > 0) {
                    time_str[time_len++] = '0' + (temp_time / div);
                    temp_time %= div;
                    div /= 10;
                }
            }
            write(1, time_str, time_len);
            write(1, "ms] % ", 6);
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
            write(1, "|", 1);
            // Write execution time
            char time_str2[20];
            int time_len2 = 0;
            long temp_time2 = exec_time_ms;
            if (temp_time2 == 0) {
                time_str2[time_len2++] = '0';
            } else {
                int div2 = 1;
                while (temp_time2 / div2 >= 10) div2 *= 10;
                while (div2 > 0) {
                    time_str2[time_len2++] = '0' + (temp_time2 / div2);
                    temp_time2 %= div2;
                    div2 /= 10;
                }
            }
            write(1, time_str2, time_len2);
            write(1, "ms] % ", 6);
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
            clock_gettime(CLOCK_REALTIME, &start_time);
            waitpid(pid, &status, 0);
            clock_gettime(CLOCK_REALTIME, &end_time);
            display_status = true;
            exec_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + 
                           (end_time.tv_nsec - start_time.tv_nsec) / 1000000;
        }
    }
    
    return 0;
}