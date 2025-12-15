#include "main.h"

#include "q1.h"
#include "q2.h"
#include "q3.h"

#include <unistd.h>
#include <string.h>
#include "q4.h"
#include "q5.h"
#include "q6.h"
#include "q7.h"
#include "q8.h"
/*

int main(void)
{
    message_bienvenue_shell();

    char prompt[PROMPT_SIZE];
    strcpy(prompt, "enseash % ");

    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        run_one_command_and_update_prompt(prompt);
    }

    return 0;
}
*/
int main(void)
{
    welcome_message_shell();

    char prompt[PROMPT_SIZE];
    strcpy(prompt, "enseash % ");

    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt));
        execute_pipe_q8(prompt);
    }

    return 0;
}
