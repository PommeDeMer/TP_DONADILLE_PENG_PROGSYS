#ifndef Q4_H
#define Q4_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE_SIZE 512
#define PROMPT_SIZE 64
void entier_vers_chaine(int nombre, char *chaine);

void run_one_command_and_update_prompt(char *prompt);

#endif
