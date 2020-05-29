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

int add_to_list(char *s, t_list *lst)
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

int		builtin_export(char **s)
{
	t_list	*lst;
	int		i;
	int		start;
	i = 1;
	while (s[i])
	{
		if ((start = check_if_exist(g_export, s[i])))
		{
			if (replace_elem(s[i], start))
				return (1);
		}
		else if (add_elem(s[i]))
			return (1);
		i++;
	}
	return(0);
}