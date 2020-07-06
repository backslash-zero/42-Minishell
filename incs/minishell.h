#ifndef MINISHELL_H
# define MINISHELL_H

# define MAX_INPUT_SIZE 131072
# define NB_BUILINS 7

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "error.h"
#include "libft.h"
#include "env.h"
#include "builtin.h"
#include "ft_printf.h"

typedef int			(*builtfunc_addr)(int fd, char **s, char **s2);

typedef struct      s_parse
{
    char      *builtnb[NB_BUILINS];
}                   t_parse;

void	ft_builtinstab(t_parse *parse);
int		ft_checkbuiltins(char **s0, char **s, t_parse *parse, int fd);
void    print_prompt_prefix(void);
void	prompt(void);
int 	launch(char *input, t_parse *parse);
void	free_tab(char **tab);
int     arg_len(char **arg);
int		ft_exec(char **arg_list);
int     redirection(char **s, char **arg, t_parse *parse);
char	**semicolon(char **arg, int i, int l);

#endif
