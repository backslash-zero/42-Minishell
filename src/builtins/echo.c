/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 10:59:32 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 11:33:19 by rzafari          ###   ########.fr       */
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

int		builtin_echo(char **arg)
{
	if (arg_len(arg) == 1)
	{
		ft_putchar('\n');
		g_ret = 0;
		return (1);
	}
	if (ft_strcmp(arg[1], "-n") == 0)
		echo_print(arg, 2);
	else
	{
		echo_print(arg, 1);
		ft_putchar('\n');
	}
	g_ret = 0;
	return (0);
}
