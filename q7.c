#include "q7.h"
#include "q4.h"          // for int_to_string (or entier_vers_chaine renamed)
#include <string.h>
#include <fcntl.h>       // open
#include <unistd.h>      // dup2, close
#include <sys/wait.h>
#include <time.h>

#define MAX_ARGS 32




/*
 
 On va gérer dans cette fonction les redirections < ou > pour écrire dans un fichier par exemple, a l'aide de la fonciton 
 * dup2 qui permet de remplacer un descripteur de fichier par un autre.
 il est utilisé pour faire pointer l’entrée ou la sortie standard du processus vers un fichier avant l’exécution de la commande.
 
 
 
 */

void execute_redirections_q7(char *prompt)
{
    char command_line[MAX_LINE_SIZE];
    char *argument_list[MAX_ARGS];
    
    char* input_file = NULL;   //contient le nom du fichier pour la redirection. 
    char* output_file = NULL;

    int argument_count = 0;
    int status;

    struct timespec start_time, end_time;
    
    int characters_read = read(STDIN_FILENO, command_line, MAX_LINE_SIZE);

   
    if (characters_read <= 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }
    command_line[characters_read - 1] = '\0';
    
    
    if (strcmp(command_line, "exit") == 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

 

    char* output_pos = strchr(command_line, '>');     // utilisés pour chercher si il y a des symboles de redirection dans la lugne de commande commme  < et >SS
    char* input_pos  = strchr(command_line, '<');
    
    
    if (output_pos != NULL) {
        *output_pos = '\0';         // coupe la commande avant '>',  La partie gauche contient maintenant uniquement la commande à exécuter
        
        output_file = output_pos + 1;   // Le nom du fichier de sortie commence juste après le caractère '>'
        while (*output_file == ' ')      // ignore les espaces
            output_file++;
    }

    if (input_pos != NULL) {
        *input_pos = '\0';			// coupe la commande avant '<'
        input_file = input_pos + 1;  // Le nom du fichier d'entrée commence juste après le caractère '<'
        while (*input_file == ' ')
            input_file++;
    }
    
   

    char *current_word = strtok(command_line, " ");      //partie dela précédente question pour exécuter les commandes avec arguments

    while (current_word != NULL) {
        argument_list[argument_count] = current_word;
        argument_count++;
        current_word = strtok(NULL, " ");
    }

    argument_list[argument_count] = NULL;
    
 

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pid_t pid = fork();

    if (pid == 0) {

       
        if (input_file != NULL) {                // redirection de l'entrée
            int input_fd = open(input_file, O_RDONLY);
            dup2(input_fd, STDIN_FILENO);  
            close(input_fd);
        }
        
        
        if (output_file != NULL) {     //redirection de la sortie
            int output_fd = open(output_file,O_WRONLY | O_CREAT | O_TRUNC,0644);    //0644 est le mode d'acces du fichier, en ecriture, + lecrture, lecture seule. On écrit, crée ou efface. 
            dup2(output_fd, STDOUT_FILENO);      // on copie output_fd sur STDOUT_FILENO
            close(output_fd);
        }

        execvp(argument_list[0], argument_list);
        exit(1);
    }
    else {
        wait(&status);
    }
    
    clock_gettime(CLOCK_MONOTONIC, &end_time);

   

    int execution_time_ms =
        (end_time.tv_sec - start_time.tv_sec) * 1000
      + (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

    char return_code[16];
    char time_string[16];

    int_to_string(execution_time_ms, time_string);

    if (WIFEXITED(status)) {

        int_to_string(WEXITSTATUS(status), return_code);

        strcpy(prompt, "enseash [exit:");
        strcat(prompt, return_code);
    }
    else if (WIFSIGNALED(status)) {
		
		int_to_string(WTERMSIG(status), return_code);

        strcpy(prompt, "enseash [sign:");
        strcat(prompt, return_code);
    }

    strcat(prompt, "|");
    strcat(prompt, time_string);
    strcat(prompt, "ms] % ");
}




