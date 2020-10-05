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

int		builtin_export_next_2(char **arg, int i, int j, char **s)
{
	int		start;

	while (arg[i] && (j = check_export_arg(arg[i])) > 0)
	{
		if ((start = check_if_exist(g_export, arg[i])))
		{
			if (!replace_elem(arg[i], start))
			{
				free_tab(s);
				return (0);
			}
		}
		else
		{
			if (!add_elem(arg[i]))
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

int		builtin_export_next(char **arg, int l, int j)
{
	char	**s;
	int		i;

	s = NULL;
	i = 1;
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
	return (builtin_export_next_2(arg, i, j, s));
}

int		builtin_export(char **arg)
{
	int		j;
	int		l;

	l = 0;
	j = 0;
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
	return (builtin_export_next(arg, l, j));
}
