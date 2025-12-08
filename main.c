#include "main.h"

#include "q1.h"
#include "q2.h"
#include "q3.h"

#include <unistd.h>
#include <string.h>
#include "q4.h"

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
