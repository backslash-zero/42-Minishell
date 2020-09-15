/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:23:45 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/14 15:26:34 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char		**last_cmd_arg(char **arg, t_pipe_cmd *pipe_cmd)
{
	int		len;
	int		j;
	char	**cmd_arg;

	len = 0;
	j = 0;
	while (arg[len])
		len++;
	if (!(cmd_arg = malloc(sizeof(char*) * len + 1)))
		return (NULL);
	while (j < len)
	{
		cmd_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	cmd_arg[j] = NULL;
	return (cmd_arg);
}

char		***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd)
{
	char	***cmd;
	int		i;
	int		cmd_arg;
	int		count;

	i = 0;
	cmd_arg = 0;
	count = 0;
	if (!(cmd = malloc(sizeof(char**) * pipe_cmd->len + 1 + 1)))
		return (NULL);
	while (count < pipe_cmd->len + 1)
	{
		if (ft_count_pipe(&arg_list[i]) != 0)
		{
			cmd[count] = cmd_arg_get(&arg_list[i], &i, pipe_cmd);
			i++;
		}
		else
		{
			cmd[count] = last_cmd_arg(&arg_list[i], pipe_cmd);
		}
		count++;
	}
	cmd[count] = NULL;
	return (cmd);
}
