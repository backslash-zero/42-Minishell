/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:17:37 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/23 15:20:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		builtin_exit_next(t_cmd *cmd, int i)
{
	unsigned int	j;

	while (cmd->arg[1][i])
	{
		if (!(ft_isdigit(cmd->arg[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, cmd->arg[1]);
			free_tool(cmd->arg, cmd->input_arg, 1);
			exit(2);
		}
		i++;
	}
	if ((i = ft_atoi(cmd->arg[1])) < 0)
	{
		j = (unsigned int)i;
	}
	else
		j = i;
	return (j);
}

int		builtin_exit_long_arg(t_cmd *cmd, int i)
{
	while (cmd->arg[1][i])
	{
		if (!(ft_isdigit(cmd->arg[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, cmd->arg[1]);
			free_tool(cmd->arg, cmd->input_arg, 1);
			exit(2);
		}
		i++;
	}
	g_ret = 1;
	return (ft_error(MANY_ARGS, NULL, NULL, cmd->arg[0]));
}

int		builtin_exit(t_cmd *cmd)
{
	int				i;
	unsigned int	j;
	int				arg_l;

	ft_putstr("exit\n");
	i = 0;
	if ((arg_l = arg_len(cmd->arg)) == 1)
	{
		free_tool(cmd->arg, cmd->input_arg, 1);
		exit(0);
	}
	if (arg_l > 2)
		return (builtin_exit_long_arg(cmd, i));
	if (cmd->arg[1][i] == '+' || cmd->arg[1][i] == '-')
		i++;
	j = builtin_exit_next(cmd, i);
	free_tool(cmd->arg, cmd->input_arg, 1);
	exit(j);
}
