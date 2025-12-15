#include "q1.h"

void welcome_message_shell(void) {
    char *str = "Bienvenue dans le Shell ENSEA.\nPour quitter taper 'exit'\n";
    write(STDOUT_FILENO, str, strlen(str));
}
