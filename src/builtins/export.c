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

char	**copy_goodarg(char **arg, int l)
{
	char	**s;
	int		d;

	d = 0;
	if (!(s = (char **)malloc(sizeof(char **) * (l + 2))))
		return (NULL);
	l = 0;
	while (arg[l])
	{
		if (ft_strlen(arg[l]) != 0)
		{
			if (!(s[d] = ft_strdup(arg[l])))
				return (NULL);
			d++;
		}
		l++;
	}
	s[d] = NULL;
	return (s);
}

int		builtin_export(char **arg)
{
	int		i;
	int		start;
	int		j;
	int		l;
	char	**s;

	i = 1;
	l = 0;
	s = NULL;
	if (arg_len(arg) == 1)
		return (print_export());
	if (arg_len(arg) > 1)
	{
		j = 1;
		while (arg[j])
		{
			if (ft_strlen(arg[j]) == 0)
				l++;
			j++;
		}
		if (l == arg_len(arg) - 1)
			return (print_export());
	}
	if (l == 0)
	{
		if ((s = copy_goodarg(arg, arg_len(arg))) == NULL)
			return (0);
	}
	else if (l < arg_len(arg) - 1)
	{
		if ((s = copy_goodarg(arg, l)) == NULL)
			return (0);
	}
	while (s[i] && (j = check_export_arg(s[i])) > 0)
	{
		if ((start = check_if_exist(g_export, s[i])))
		{
			if (!replace_elem(s[i], start))
			{
				free_tab(s);
				return (0);
			}
		}
		else
		{
			if (!add_elem(s[i]))
			{
				free_tab(s);
				return (0);
			}
		}
		i++;
	}
	free_tab(s);
	return (export_return(arg, j));
}
