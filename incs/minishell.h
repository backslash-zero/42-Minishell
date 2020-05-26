#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void    print_prompt_prefix(void);
void    shell_loop(void);
void    ft_print(char *s);

#endif
