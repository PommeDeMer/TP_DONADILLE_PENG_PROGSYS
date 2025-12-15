#ifndef Q6_H
#define Q6_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#include "q4.h"

#define MAX_LINE_SIZE 512
#define MAX_ARGS 32
#define PROMPT_SIZE 64

void execute_multiple_arguments_q6(char *prompt);

#endif
