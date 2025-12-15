#include "q8.h"
#include "q4.h"
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

void execute_pipe_q8(char *prompt)
{
    char command_line[MAX_LINE_SIZE];
    char *left_args[32];
    char *right_args[32];
    
    int status;
    int pipe_fd[2];

    struct timespec start_time, end_time;

    int bytes_read = read(STDIN_FILENO, command_line, MAX_LINE_SIZE);
    if (bytes_read <= 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

    command_line[bytes_read - 1] = '\0';
    
    if (strcmp(command_line, "exit") == 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

   

    char* pipe_pos = strchr(command_line, '|');      // Recherche du caractère '|' dans la ligne de commande afin de détecter une redirection de type pipe
    if (pipe_pos == NULL) {
        return;
    }

    *pipe_pos = '\0';     // On remplace le caractère '|' par '\0' pour couper la chaîne en deux  parties indépendantes
  

    char* left_command  = command_line;    //la partie gauche correspond a la premiere commanded
    char* right_command = pipe_pos + 1;    //la droite est la suivante
    
    while (*right_command == ' ') {   //suppression des espaces
        right_command++;
    }


    int i = 0;   //découpage des arguemnts q6
    char* token = strtok(left_command, " ");
    while (token != NULL) {
        left_args[i++] = token;
        token = strtok(NULL, " ");
    }
    left_args[i] = NULL;
    
    i = 0;
    token = strtok(right_command, " ");
    while (token != NULL) {
        right_args[i++] = token;
        token = strtok(NULL, " ");
    }
    right_args[i] = NULL;
    

    clock_gettime(CLOCK_MONOTONIC, &start_time);

    pipe(pipe_fd);
    
    pid_t pid1 = fork();
    if (pid1 == 0) {
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execvp(left_args[0], left_args);
        exit(1);
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[1]);
        close(pipe_fd[0]);
        execvp(right_args[0], right_args);
        exit(1);
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    clock_gettime(CLOCK_MONOTONIC, &end_time);

    int execution_time_ms =(end_time.tv_sec - start_time.tv_sec) * 1000 +(end_time.tv_nsec - start_time.tv_nsec) / 1000000;
        
    char code_str[16];
    char time_str[16];

    int_to_string(execution_time_ms, time_str);

    if (WIFEXITED(status)) {
        int_to_string(WEXITSTATUS(status), code_str);
        strcpy(prompt, "enseash [exit:");
    }
    else {
        int_to_string(WTERMSIG(status), code_str);
        strcpy(prompt, "enseash [sign:");
    }

    strcat(prompt, code_str);
    strcat(prompt, "|");
    strcat(prompt, time_str);
    strcat(prompt, "ms] % ");
}

        
        





