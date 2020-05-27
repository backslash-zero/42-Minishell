#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT_SIZE 131072

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void    ft_print(char *s);
void    ft_putstr(char *s);
void    print_prompt_prefix(void);
void	prompt(void);
void	launch(char *input);
void	free_tab(char **tab);

#endif
