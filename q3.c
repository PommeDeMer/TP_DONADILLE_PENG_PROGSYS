#include "q3.h"

void bye_bye_ctrld() {

    char user_input[MAX_LINE_SIZE];
    int bytes_read = read(STDIN_FILENO, user_input, MAX_LINE_SIZE);

    if (bytes_read == 0) {   // gefstion de ctrl d, crtl d-> end of file ->read() = . 
        write(STDOUT_FILENO, "Bye bye...\n", 11);   // il y a  octets a écrire dans bye bye...,  en comptant l'espace,  en comptant 
        exit(0);
    }
   
    user_input[bytes_read -1] = '\0';
    if (strcmp(user_input, "exit") == 0) {    //ici on gere exit en comparant la chaine de caratere envoyée au clavier avec 'exit' pour détermineer si on dit bye ou ps
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

    pid_t pid = fork();

    if (pid == 0) {
        execlp(user_input, user_input, NULL);
        exit(EXIT_FAILURE);
    } 
    else {
        wait(NULL);
    }
}
