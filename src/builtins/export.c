#include "../../incs/minishell.h"

int		check_if_exist(t_list *lst, char *s)
{
	t_list	*lst2;
	char	*name;
	char	*tmp;
	int	i;

	i = 0;
	while (s[i] != '=' && s[i] != '\0')
		i++;
	if (i > 0)
		name = ft_substr(s, 0, i);
	else
		return (0);
	while (lst)
	{
		i = 0;
		lst2 = lst->next;
		while (lst->content[i] != '=' && lst->content[i])
			i++;
		tmp = ft_substr(lst->content, 0, i);
		if (ft_strcmp(name, tmp) == 0)
		{
			free (name);
			free (tmp);
			return (i);
		}
		free (tmp);
		lst = lst2;
	}
	free (name);
	return (0);
}

int	set_value(t_list *lst, char *s1, char *s2)
{
	t_list	*lst2;
	char	*tmp;
	char	*value;

	if (!(value = ft_strdup(s1)))
		return (0);
	while (lst)
	{
		if (ft_strcmp(lst->content, s2) == 0)
		{
			tmp = lst->content;
			lst->content = value;
			free (tmp);
		}
		lst = lst->next;
	}
	return (1 );
}

int	replace_elem(char *s, int i)
{
	char *s1;

	if (ft_strchr(s, '='))
	{
			s1 = ft_substr(s, 0, i + 1);
			if (!set_value(g_export, s, s1))
				return (0);
			if (!set_value(g_env, s, s1))
				return (0);
			free(s1);;
	}
	return (1);
}

int add_to_list(char *s, t_list **lst)
{
	t_list *lst1;

	if (!(lst1 = malloc(sizeof(t_list))))
		return(0);
	if (!(lst1->content = ft_strdup(s)))
		return (0);
	lst1->next = 0;
	ft_lstadd_back(lst, lst1);
	return (1);
}

int add_elem(char *s)
{
	if (!add_to_list(s, &g_export))
		return (0); 
	if (ft_strchr(s, '='))
	{
		if (!add_to_list(s, &g_env))
			return (0);
	}
	return (1);
}

int        print_export(char **arg)
{
    t_list *tmp;
    
    tmp = g_export;
    while(tmp)
    {
        ft_putstr(tmp->content);
        ft_putstr("\n");
        tmp = tmp->next;
    }
    return(0);
}

int		check_export_arg(char *arg)
{
	int i;

	i = 0;
	if ((arg[0] >= 65 && arg[0] <= 90) || (arg[0] >= 97 && arg[0] <= 122) || arg[0] == 95)
	{
		i++;
		while (arg[i] && arg[i] != '=')
		{
			if ((arg[0] >= 65 && arg[0] <= 90) || (arg[0] >= 97 && arg[0] <= 122) || arg[0] == 95 || (arg[i] >= 48 && arg[i] <= 57))
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

int		builtin_export(char **arg)
{
	t_list	*lst;
	int		i;
	int		start;
	int		j;
	i = 1;

	if (arg_len(arg) == 1)
	{
		print_export(arg);
		return (1);
	}
	while (arg[i] && (j = check_export_arg(arg[i])))
	{
		if ((start = check_if_exist(g_export, arg[i])))
		{
			if (replace_elem(arg[i], start))
				return (1);
			else
				return (0);
		}
		else 
		{
			if (add_elem(arg[i]))
				return (1);
			else
				return (0);
		}
		i++;
	}
	if (j == 0)
	{
		ft_putstr("Arg error\n");
		builtin_exit(arg);
	}
	return(0);
}