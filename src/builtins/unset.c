/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:41:57 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/18 16:11:50 by rzafari          ###   ########.fr       */
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

int		check_unset_arg(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == 45)
		return (-1);
	if (arg[0] == '(' || arg[0] == ')')
		return (-2);
	if ((arg[0] >= 65 && arg[0] <= 90) || (arg[0] >= 97 && arg[0] <= 122)
	|| arg[0] == 95 || arg[i] == 32)
		return (1);
	return (0);
}

int		builtin_unset(char **arg)
{
	int	i;
	int j;

	i = 1;
	if (arg_len(arg) == 1)
		return (0);
	if ((j = check_unset_arg(arg[i])) > 0)
	{
		while (arg[i] != NULL)
		{
			g_env = unset_env(g_env, arg[i]);
			g_export = unset_env(g_export, arg[i]);
			i++;
		}
	}
	if (j == 0)
		return (ft_error(INVALID_ID_U, NULL, NULL, arg[1]));
	if (j == -1)
		return (ft_error(INVALID_OPT_ID_U, NULL, NULL, arg[1]));
	if (j == -2)
		return (ft_error(SYNTAX_ERR, NULL, NULL, arg[1]));
	return (0);
}
