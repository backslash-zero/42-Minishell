/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:41:57 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/16 11:47:00 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		find_elem(char *s1, char *s2)
{
	int		i;
	char	*s3;

	i = 0;
	while (s1[i] != '=' && s1[i] != '\0')
		i++;
	if (!(s3 = ft_substr(s1, 0, i)))
		return (0);
	if (ft_strcmp(s3, s2) == 0)
	{
		free(s3);
		return (1);
	}
	free(s3);
	return (0);
}

t_list	*unset_env(t_list *lst, char *s)
{
	t_list	*lst2;
	t_list	*lst3;

	lst2 = lst;
	if (find_elem(lst2->content, s))
	{
		lst = lst->next;
		ft_lstdelone(lst2, free);
		return (lst);
	}
	else
	{
		lst3 = lst2->next;
		while (lst3 != NULL)
		{
			if (find_elem(lst3->content, s))
			{
				lst2->next = lst3->next;
				ft_lstdelone(lst3, free);
				return (lst);
			}
			lst2 = lst3;
			lst3 = lst3->next;
		}
		return (lst);
	}
}

int		builtin_unset(char **arg)
{
	int	i;

	i = 1;
	while (arg[i] != NULL)
	{
		g_env = unset_env(g_env, arg[i]);
		g_export = unset_env(g_export, arg[i]);
		i++;
	}
	return (0);
}
