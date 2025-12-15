#include "q5.h"
#include "q4.h"

 


/*
  danscette fonction on va reprendre le fonctionnement de la q4 en mesurant le temps d'exécution d'un processus. 
   
  On va utiliser la structure time suivante que j'ai choppé sur un site de IBM 
   
   #include <time.h>
int clock_gettime(clockid_t clockid, struct timespec *tp);
   
   struct timespec {
    time_t   tv_sec;        // seconds 
    long     tv_nsec;       // nanoseconds 
};


 */
void chopper_le_temps_q5(char* prompt)
{
    char commande[MAX_LINE_SIZE];
    int status;
    struct timespec debut, fin;

    int nb_lus = read(STDIN_FILENO, commande, MAX_LINE_SIZE);
    if (nb_lus <= 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);    //gestion de quittage crtld d et exit comme avant
    }
    commande[nb_lus- 1] = '\0';      

    if (strcmp(commande, "exit") == 0) {
        write(STDOUT_FILENO, "Bye bye...\n", 11);
        exit(0);
    }

    clock_gettime(CLOCK_MONOTONIC, &debut);         // Début de la mesure du temps d'exécution 
    //write(STDOUT_FILENO, *debut, 16);

    pid_t pid = fork();

    if (pid == 0) {

        execlp(commande, commande, NULL); // on exécute la commande si on est dans le processsus fils. 
        exit(1);
    }
    else {
      
        wait(&status);     
    }

    clock_gettime(CLOCK_MONOTONIC, &fin);              // fin de la mesure temporelle et on fait la différence. 

    int temps_exec = (fin.tv_sec -debut.tv_sec) *1000+(fin.tv_nsec -debut.tv_nsec) /1000000;
                 

    char code_str[16];
    char temps_str[16];

   
    int_to_string(temps_exec, temps_str);   //We still dont use print 
    
    
    if (WIFEXITED(status) == 1) {
        
        entier_vers_chaine(WEXITSTATUS(status), code_str);

        strcpy(prompt, "enseash [exit:");
        strcat(prompt, code_str);
        strcat(prompt, "|");
        strcat(prompt, temps_str);
        strcat(prompt, "ms] % ");
    }
    else if (WIFSIGNALED(status) == 1) {
       
        int_to_string(WTERMSIG(status), code_str);

        strcpy(prompt, "enseash [sign:");
        strcat(prompt, code_str);
        strcat(prompt, "|");
        strcat(prompt, temps_str);
        strcat(prompt, "ms] % ");
    }
}

    
