/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 17:45:00 by celestin          #+#    #+#             */
/*   Updated: 2020/09/21 17:48:24 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	sort_export(t_list *lst)
{
	t_list	*lst1;
	void	*cont;
	int		i;

	if (!lst)
		return ;
	lst1 = lst;
	i = ft_lstsize(g_export);
	while (i)
	{
		while (lst)
		{
			while (lst->next && ft_strcmp(lst->content, lst->next->content) > 0)
			{
				cont = lst->next->content;
				lst->next->content = lst->content;
				lst->content = cont;
			}
			lst = lst->next;
		}
		lst = lst1;
		i--;
	}
}

int		print_export(void)
{
	t_list	*tmp;
	int		i;

	sort_export(g_export);
	tmp = g_export;
	while (tmp != NULL)
	{
		i = 0;
		ft_putstr_fd(1, "declare -x ");
		if (ft_strchr(tmp->content, '='))
		{
			while (tmp->content[i] != '=')
				ft_putchar_fd(1, tmp->content[i++]);
			ft_putchar_fd(1, tmp->content[i++]);
			ft_putstr_fd(1, "\"");
			while (tmp->content[i])
				ft_putchar_fd(1, tmp->content[i++]);
			ft_putstr_fd(1, "\"");
		}
		else
			ft_putstr_fd(1, tmp->content);
		ft_putstr_fd(1, "\n");
		tmp = tmp->next;
	}
	return (1);
}

int		check_export_arg_next(char *arg, int i)
{
	if (arg[i] == '=')
	{
		i++;
		while (arg[i])
		{
			if ((arg[i] >= 65 && arg[i] <= 90) || (arg[i] >= 97 &&
			arg[i] <= 122) || arg[i] == 95 || arg[i] == 45 || arg[i] == 32 ||
			(arg[i] >= 48 && arg[i] <= 57) || arg[i] == 58 || arg[i] == 47)
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int		export_return(char **arg, int j)
{
	if (j == 0 || j == -1 || j == -2)
		g_ret = 1;
	if (j == 0)
		return (ft_error(INVALID_ID_X, NULL, NULL, arg[1]));
	if (j == -1)
		return (ft_error(INVALID_OPT_ID_X, NULL, NULL, arg[1]));
	if (j == -2)
		return (ft_error(SYNTAX_ERR, NULL, NULL, arg[1]));
	g_ret = 0;
	return (0);
}
