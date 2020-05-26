#ifndef MINISHELL_H
# define MINISHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void    ft_print(char *s);
void    print_prompt_prefix(void);

#endif
