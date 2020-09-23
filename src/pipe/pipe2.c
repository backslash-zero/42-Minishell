/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:23:45 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 23:35:15 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		init_t_pipe(t_pipe_cmd *pipe_cmd, char **arg_list)
{
	if (!(pipe_cmd->tab_env = tablst(g_env)))
		return (0);
	pipe_cmd->check_redir = 0;
	pipe_cmd->len = ft_count_pipe(arg_list);
	pipe_cmd->cmd = prepare_cmd(arg_list, pipe_cmd);
	pipe_cmd->fd_in = 0;
	pipe_cmd->i = 0;
	return (1);
}

int		ft_pipe_2(char **arg_list, t_cmd *cmd)
{
	t_pipe_cmd	pipe_cmd;

	if (!init_t_pipe(&pipe_cmd, arg_list))
		return (0);
	loop_pipe(&pipe_cmd, cmd);
	if (g_ret == 127)
		return (-1);
	return (0);
}

char	**cmd_arg_get(char **arg, int *i)
{
	int		cmd_arg_len;
	int		j;
	char	**cmd_arg;

	cmd_arg_len = 0;
	j = 0;
	while (ft_strcmp(arg[cmd_arg_len], "|"))
		cmd_arg_len++;
	*i += cmd_arg_len;
	if (!(cmd_arg = (char **)malloc(sizeof(char*) * cmd_arg_len + 1)))
		return (NULL);
	while (j < cmd_arg_len)
	{
		cmd_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	cmd_arg[j] = NULL;
	return (cmd_arg);
}

char	**last_cmd_arg(char **arg)
{
	int		len;
	int		j;
	char	**cmd_arg;

	len = 0;
	j = 0;
	while (arg[len])
		len++;
	printf("lssss\n");
	if (!(cmd_arg = (char **)malloc(sizeof(char*) * len + 1)))
		return (NULL);
	while (j < len)
	{
		cmd_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	cmd_arg[j] = NULL;
	return (cmd_arg);
}


char	***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd)
{
	char	***cmd;
	int		i;
	int		cmd_arg;
	int		count;

	i = 0;
	cmd_arg = 0;
	count = 0;
	if (!(cmd = (char ***)malloc(sizeof(char**) * pipe_cmd->len + 1 + 1)))
		return (NULL);
	printf("pipe_cmd_len = %d\n",pipe_cmd->len );
	while (count < pipe_cmd->len + 1)
	{
		if (ft_count_pipe(&arg_list[i]) != 0)
		{
			cmd[count] = cmd_arg_get(&arg_list[i], &i);
			i++;
		}
		else
		{
			cmd[count] = last_cmd_arg(&arg_list[i]);
		}
		count++;
	}
	cmd[count] = NULL;
	count++;
	cmd[count] = NULL;
	return (cmd);
}
