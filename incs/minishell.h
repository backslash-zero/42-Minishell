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
#include "libft.h"

typedef int			(*builtfunc_addr)(char **s);
typedef struct      s_parse
{
    char      *builtnb[NB_BUILINS];
}                   t_parse;


void    ft_putstr(char *s);
void	ft_putchar(char c);
void    print_prompt_prefix(void);
void	prompt(void);
void	launch(char *input, t_parse *parse);
void	free_tab(char **tab);
int		ft_echo(char **s);
int		ft_cd(char **s);
int		ft_pwd(char **s);
int		ft_export(char **s);
int		ft_unset(char **s);
int		ft_env(char **s);
int		ft_exit(char **s);

#endif
