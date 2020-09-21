/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 12:04:56 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 17:45:24 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		check_export_arg(char *arg)
{
	int i;

	i = 0;
	if (arg[0] == 36)
		return (print_export());
	if (arg[0] == 45)
		return (-1);
	if (arg[0] == '(' || arg[0] == ')')
		return (-2);
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

int		builtin_export(char **arg)
{
	t_list	*lst;
	int		i;
	int		start;
	int		j;

	i = 1;
	if (arg_len(arg) == 1)
		return (print_export());
	while (arg[i] && (j = check_export_arg(arg[i])) > 0)
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
	return (export_return(arg, j));
}
