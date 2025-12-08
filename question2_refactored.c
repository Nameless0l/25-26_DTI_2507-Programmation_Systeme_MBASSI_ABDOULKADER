#include "question1.h"
#include "question2.h"
#include "constantes.h"

int main() {
    // Question 1: Display welcome message
    print_welcome_message();
    
    // Question 2: REPL - Read-Eval-Print Loop
    char command[TAILLE_MAX_COMMANDE];
    ssize_t bytes_read;
    
    while (1) {
        // Display prompt
        display_prompt();
        
        // Read command from user
        bytes_read = read_command(command, TAILLE_MAX_COMMANDE);
        
        if (bytes_read <= 0) {
            // EOF (Ctrl+D) or read error
            break;
        }
        
        // Check for exit command
        if (is_exit_command(command)) {
            break;
        }
        
        // Execute the command
        execute_command(command);
    }
    
    return 0;
}
