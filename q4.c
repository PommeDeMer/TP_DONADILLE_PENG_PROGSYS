#include "q4.h"

void int_to_string(int number, char *string)
{
    char temp[16];
    int count = 0;
    int i;

    if (number == 0) {   // case where the number is 0
        string[0] = '0';
        string[1] = '\0';
        return;
    }
    
    while (number > 0) {  // extract digits from the number starting from the end
        temp[count] = '0' + (number % 10);
        number = number / 10;
        count++;
    }

    for (i = 0; i < count; i++) {  // rewrite the digits in the correct order
        string[i] = temp[count - i - 1];
    }

    string[i] = '\0';
}


void run_one_command_and_update_prompt(char* prompt)         // we factorize the code in 3 parts and run it on a loop in the main, first we check for the user imput, then fork the process and execute the command and construct the output. 
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
    
    pid_t pid = fork();             // we fork the process

    if (pid == 0) {
        execlp(input, input, NULL);
        exit(1);
    } else {
        wait(&status);
    }


    char number[16];     // on met a jour le prompt

    if (WIFEXITED(status)) {    // on recpere le  code de retour du processur fils avec WEXITSTATUS()
        int_to_string(WEXITSTATUS(status), number);     // On connstruire le prompt
        strcpy(prompt, "enseash [exit:");
        strcat(prompt, number);
        strcat(prompt, "] % ");
    }
    
    else if (WIFSIGNALED(status)) {      // idem si le processus a été interrompu par un signal
        int_to_string(WTERMSIG(status), number);
        strcpy(prompt, "enseash [sign:");
        strcat(prompt, number);
        strcat(prompt, "] % ");
    }
}
