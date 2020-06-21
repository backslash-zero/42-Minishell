#include "../../incs/minishell.h"

char	*get_var(t_list *list, char *key)
{
    t_list *tmp;

    tmp = list;
    while(tmp)
    {
        if (!(ft_strncmp(tmp->content, key, (int)ft_strlen(key))))
                return (ft_strdup((char *)&(tmp->content)[ft_strlen(key)]));
        tmp = tmp->next;
    }
    return (NULL);
}

int		set_var(t_list *list, char *key, char *value)
{
	t_list  *tmp;
    char    *old;
    char    *new;

    tmp = list;
    if (!value)
	{
		if (!(new = ft_strdup(key)))
			return (-1);
	}
	else if (!(new = ft_strjoin(key, value)))
		return (-1);
    while(tmp)
    {
        if (!(ft_strncmp(tmp->content, key, ft_strlen(key))))
        {
            old = tmp->content;
            tmp->content = new;
            free(old);
        }
        tmp = tmp->next;
    }
    return (1);
}
	

t_list    *init_env(t_list **lst, char **tab)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = NULL;
	while (tab[i])
	{
		if (!(temp = malloc(sizeof(t_list))))
			return (NULL);
		if (!(temp->content = ft_strdup(tab[i])))
			return (NULL);
		temp->next = 0;
		ft_lstadd_back(lst, temp);
		i++;
	}
	return (*lst);
}

int        builtin_env(int fd, char **arg)
{
    t_list *tmp;
    
    tmp = g_env;
    while(tmp)
    {
        ft_putstr_fd(fd, tmp->content);
        ft_putstr_fd(fd, "\n");
        tmp = tmp->next;
    }
    return(0);
}