#include "q4.h"

void int_to_str(int nombre, char *chaine)
{
    char temp[16];
    int compteur = 0;
    int i;

    if (nombre == 0) {   // cas de 0
        chaine[0] = '0';
        chaine[1] = '\0';
        return;
    }

    while (nombre > 0) {  //  On récupère les chiffres du nombre en partant de la fin
        temp[compteur] = '0' + (nombre % 10);
        nombre = nombre / 10;
        compteur++;
    }

    for (i = 0; i < compteur; i++) {  //on réécrit les ciffres a l'endroit
        chaine[i] = temp[compteur - i - 1];
    }

    chaine[i] = '\0';
}


void run_one_command_and_update_prompt(char *prompt)
{
    char input[MAX_LINE_SIZE];
    int status = 0;

    int n = read(STDIN_FILENO, input, MAX_LINE_SIZE);

    if (n <= 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

    input[n-1] = '\0';

    if (strcmp(input, "exit") == 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }
    
    pid_t pid = fork();

    if (pid == 0) {
        execlp(input, input, NULL);
        exit(1);
    } else {
        wait(&status);
    }


    char number[16];     // on met a jour le prompt

    if (WIFEXITED(status)) {    // on recpere le  code de retour du processur fils avec WEXITSTATUS()
        int_to_str(WEXITSTATUS(status), number);     // On connstruire le prompt
        strcpy(prompt, "enseash [exit:");
        strcat(prompt, number);
        strcat(prompt, "] % ");
    }
    
    else if (WIFSIGNALED(status)) {      // idem si le processus a été interrompu par un signal
        int_to_str(WTERMSIG(status), number);
        strcpy(prompt, "enseash [sign:");
        strcat(prompt, number);
        strcat(prompt, "] % ");
    }
}
