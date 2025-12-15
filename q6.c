#include "q6.h"
#include "q4.h"




/*
 
 On utilise la fonction strtok pour séparer les arguments 
 * 
 * code inspiration: doc strtok
 // La chaine de caractères à traiter.
    char str[] = "- Voici une phrase avec quelques séparateurs ! -";
    // La définitions de séparateurs connus.
    const char * separators = " ,.-!";

    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
 char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        printf ( "%s\n", strToken );
        // On demande le token suivant.
        strToken = strtok ( NULL, separators );
    }
 
 
 
 On utilise aussi execvp 
 * #include <unistd.h>
int execvp(const char *command, char* argv[]);
 
 
 
 
 */


void execute_multiple_arguments_q6(char* prompt)
{
    char command_line[MAX_LINE_SIZE];     
    char* argument_list[32];              // tableau d'arguments pour execvp
    int argument_count = 0;
    int status;

    struct timespec start_time, end_time;

    int number_of_characters_read = read(STDIN_FILENO,command_line, MAX_LINE_SIZE);
    
    if (number_of_characters_read <= 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

   
    command_line[number_of_characters_read - 1] = '\0';
    
    if (strcmp(command_line, "exit") == 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }
   
     
    char* current_word = strtok(command_line, " ");          //début du découpage avec strtoken, le premier avant la boucle
    
    while (current_word != NULL) {       // on continue la boucle tant que strtok ne renvoie pas NULL
        argument_list[argument_count] = current_word;
        argument_count++;
        current_word = strtok(NULL, " ");
    }
    
    argument_list[argument_count] = NULL;  //le dernier mot est forcément NULL en fin de chaine

   

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pid_t pid = fork();
    
    if (pid == 0) {
       
        execvp(argument_list[0], argument_list);   // la commande est le premeir mot extrait et les arguments sont ensuite dans le tableau
        exit(1);
    }
    
    else {
       
        wait(&status);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    
    int execution_time_ms = (end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

    char return_code[16];
    char time_string[16];
    
    int_to_string(execution_time_ms, time_string);

  
    if (WIFEXITED(status)) {
		
		int_to_string(WEXITSTATUS(status), return_code);

        strcpy(prompt, "enseash [exit:");
        strcat(prompt, return_code);
        strcat(prompt, "|");
        strcat(prompt, time_string);
        strcat(prompt, "ms] % ");
    }
    
    else if (WIFSIGNALED(status)) {
		
		int_to_string(WTERMSIG(status), return_code);      // fin par signal 

        strcpy(prompt, "enseash [sign:");
        strcat(prompt, return_code);
        strcat(prompt, "|");
        strcat(prompt, time_string);
        strcat(prompt, "ms] % ");
    }
}




                                    
