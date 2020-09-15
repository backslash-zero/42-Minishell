/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_next.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:10:10 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/14 13:59:00 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		add_to_list(char *s, t_list **lst)
{
	t_list *lst1;

	if (!(lst1 = malloc(sizeof(t_list))))
		return (0);
	if (!(lst1->content = ft_strdup(s)))
		return (0);
	lst1->next = NULL;
	ft_lstadd_back(lst, lst1);
	return (1);
}

int		set_value(t_list *lst, char *s1, char *s2)
{
	t_list	*lst2;
	char	*tmp;
	char	*value;
	char	*s3;
	int		i;

	if (!(value = ft_strdup(s1)))
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] != '=' && lst->content[i])
			i++;
		s3 = ft_substr(lst->content, 0, i);
		if (ft_strcmp(s3, s2) == 0)
		{
			tmp = lst->content;
			lst->content = value;
			free(tmp);
			return (1);
		}
		lst = lst->next;
		free(s3);
	}
	return (0);
}

int		add_elem(char *s)
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

int		replace_elem(char *s, int i)
{
	char *s1;

	if (ft_strchr(s, '='))
	{
		s1 = ft_substr(s, 0, i);
		if (set_value(g_export, s, s1))
		{
			if (!set_value(g_env, s, s1))
			{
				if (!add_to_list(s, &g_env))
					return (0);
			}
			free(s1);
		}
		else
		{
			free(s1);
			return (0);
		}
	}
	return (1);
}

int		check_if_exist(t_list *lst, char *s)
{
	t_list	*lst2;
	char	*name;
	char	*tmp;
	int		i;

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
			free(name);
			free(tmp);
			return (i);
		}
		free(tmp);
		lst = lst2;
	}
	free(name);
	return (0);
}
