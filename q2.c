#include <unistd.h>     
#include <string.h>    
#include <stdlib.h>     
#include <sys/types.h>  
#include <sys/wait.h>   
#include "q2.h"

void execute_one_simple_command(){
	
	
	char user_input[MAX_LINE_SIZE];
    int number_of_bytes_read = read(STDIN_FILENO, user_input, MAX_LINE_SIZE);
	user_input[number_of_bytes_read - 1] = '\0';  // enlever le \n

    pid_t child_process_id = fork();

    if (child_process_id == 0) {
        execlp(user_input, user_input, NULL);
        exit(EXIT_FAILURE);   //On sort pour éviter d'avoir des processsus pendant (vérifiable sur ps -a) 
    } 
    else {
        wait(NULL);
    }

}
	
	






















  
