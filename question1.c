#include<stdio.h>
#include <unistd.h>


int main() {
    // Display a welcome message, followed by a simple prompt. Example:
    // $ ./enseash
    // Welcome to ENSEA Shell.
    // To exit, type 'exit'.
    // enseash %


    write(1, "\nWelcome to ENSEA Shell.\n", 25);
    write(1, "\nTo exit, type 'exit'.\n", 23);
    write(1, "enseash % \n", 11);


    return 0;
}