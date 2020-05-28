#ifndef ENV_H
# define ENV_H

#include "libft.h"

t_list	*g_env;
t_list	*g_export;

t_list  *init_env(t_list **lst, char **tab);
int	    set_var(t_list *list, char *key, char *value);
char    *get_var(t_list *list, char *key);
t_list  *init_env(t_list **lst, char **tab);

#endif