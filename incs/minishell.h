#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT_SIZE 131072
# define NB_BUILINS 7

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "error.h"
#include "libft.h"
#include "env.h"
#include "builtin.h"

typedef int			(*builtfunc_addr)(char **s);
typedef struct      s_parse
{
    char      *builtnb[NB_BUILINS];
}                   t_parse;

void    print_prompt_prefix(void);
void	prompt(void);
void	launch(char *input, t_parse *parse);
void	free_tab(char **tab);
int     arg_len(char **arg);

#endif
