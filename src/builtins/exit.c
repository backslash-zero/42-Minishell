/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:17:37 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/18 17:01:46 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		builtin_exit_next(char **arg, int i)
{
	unsigned int j;
	
	while (arg[1][i])
	{
		if (!(ft_isdigit(arg[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, arg[1]);
			exit(255);
		}
		i++;
	}
	if ((i = ft_atoi(arg[1])) < 0)
	{
		j = (unsigned int)i;
	}
	else
		j = i;
	return (j);
}

int		builtin_exit(char **arg)
{
	int				i;
	unsigned int	j;
	int				arg_l;

	ft_putstr("exit\n");
	i = 0;
	if ((arg_l = arg_len(arg)) == 1)
	{
		free_tab(arg);
		exit(0);
	}
	if (arg_l > 2)
		return (ft_error(MANY_ARGS, NULL, NULL, arg[1]));
	if (arg[1][i] == '+' || arg[1][i] == '-')
		i++;
	j = builtin_exit_next(arg, i);
	exit(j);
}
