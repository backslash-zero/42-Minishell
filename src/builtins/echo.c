/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:59:32 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 17:39:51 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	echo_print(char **arg, int i)
{
	while (arg[i])
	{
		if (arg[i][0] != '\0')
			ft_putstr(arg[i]);
		i++;
		if (arg[i])
			ft_putchar(' ');
	}
}

int		echo_lonely(void)
{
	ft_putchar('\n');
	g_ret = 0;
	return (1);
}

int		echo_n(char **arg, int i)
{
	int j;
	int n;

	while (arg[i])
	{
		j = 0;
		n = 0;
		while (arg[i][j])
		{
			n = (i == 1 && arg[i][j + 1] != 'n') ? 1 : 0;
			if (arg[i][j] == '-' || arg[i][j] == 'n')
				j++;
			else
			{
				echo_print(arg, i);
				if (n == 1)
					ft_putchar('\n');
				g_ret = 0;
				return (0);
			}
		}
		i++;
	}
	g_ret = 0;
	return (0);
}

int		builtin_echo(char **arg)
{
	int i;

	(void)arg;
	if (arg_len(arg) == 1)
		return (echo_lonely());
	i = 1;
	if (arg[i][0] == '-')
		return (echo_n(arg, i));
	else
	{
		echo_print(arg, 1);
		ft_putchar('\n');
	}
	g_ret = 0;
	return (0);
}
