/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 12:04:56 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/18 14:28:15 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		check_export_arg_next(char *arg, int i)
{
	if (arg[i] == '=')
	{
		i++;
		while (arg[i])
		{
			if ((arg[i] >= 65 && arg[i] <= 90) || (arg[i] >= 97 &&
			arg[i] <= 122) || arg[i] == 95 || arg[i] == 45 || arg[i] == 32 ||
			(arg[i] >= 48 && arg[i] <= 57))
				i++;
			else
				return (0);
		}
	}
	return (1);
}

int		check_export_arg(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == 45)
		return (-1);
	if ((arg[0] >= 65 && arg[0] <= 90) || (arg[0] >= 97 && arg[0] <= 122)
	|| arg[0] == 95 || arg[i] == 32)
	{
		i++;
		while (arg[i] && arg[i] != '=')
		{
			if ((arg[i] >= 65 && arg[i] <= 90) || (arg[i] >= 97 &&
			arg[i] <= 122) || arg[i] == 95 || arg[i] == 32 ||
			(arg[i] >= 48 && arg[i] <= 57))
				i++;
			else
				return (0);
		}
		return (check_export_arg_next(arg, i));
	}
	return (0);
}

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

int		builtin_export(char **arg)
{
	t_list	*lst;
	int		i;
	int		start;
	int		j;

	i = 1;
	if (arg_len(arg) == 1)
		return (print_export());
	while (arg[i] && (j = check_export_arg(arg[i]) > 0))
	{
		if ((start = check_if_exist(g_export, arg[i])))
		{
			if (!replace_elem(arg[i], start))
				return (0);
		}
		else
		{
			if (!add_elem(arg[i]))
				return (0);
		}
		i++;
	}
	if (j == 0)
		return (ft_error(INVALID_ID_X, NULL, NULL, arg[1]));
	if (j == -1)
		return (ft_error(INVALID_OPT_ID_X, NULL, NULL, arg[1]));
	return (0);
}
