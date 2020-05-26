#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void    print_prompt_prefix(void);
void    shell_loop(void);

#endif