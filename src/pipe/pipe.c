/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/03 18:22:34 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		ft_count_pipe(char **arg)
{
	int i = 0;
	int count = 0;

	while (arg[i])
	{
		if (!ft_strcmp(arg[i],"|"))
			count++;
		i++;
	}
	return (count);
}

char		**cmd_arg_get(char **arg, int *i)
{
	int cmd_arg_len = 0;

	while (ft_strcmp(arg[cmd_arg_len], "|"))
		cmd_arg_len++;
	*i += cmd_arg_len;
	char **cmd_arg;
	if (!(cmd_arg = malloc(sizeof(char*) * cmd_arg_len + 1)))
		return (NULL);
	int j = 0;
	while (j < cmd_arg_len)
	{
		cmd_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	cmd_arg[j] = NULL;	
	return (cmd_arg);
}

char		**last_cmd_arg(char **arg)
{
	int len = 0;
	char **cmd_arg;
	int j = 0;

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

char		***prepare_cmd(char **arg_list, int pipe_len)
{
	char ***cmd;
	int i = 0;
	int cmd_arg = 0;
	int count = 0;

	if (!(cmd = malloc(sizeof(char**) * pipe_len + 1 + 1)))
		return (NULL);
	while (count < pipe_len + 1)
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
	return (cmd);
}

int		loop_pipe(t_pipe_cmd *pipe_cmd)
{
	while (pipe_cmd->cmd[pipe_cmd->i])
	{
		pipe(pipe_cmd->pfd);
		if ((pipe_cmd->proc = fork()) == -1)
		{
			free_tab(pipe_cmd->tab_env);
			return (-1);
		}
		else if (pipe_cmd->proc == 0)
		{
			// check redirection + open file + assign to struct + t_pipe_cmd_2_t_cmd
			dup2(pipe_cmd->fd_in, 0);
			if (pipe_cmd->cmd[pipe_cmd->i + 1] != NULL)
				dup2(pipe_cmd->pfd[1], 1);
			close(pipe_cmd->pfd[0]);
			pipe_cmd->s = find_path_env(pipe_cmd->tab_env, pipe_cmd->cmd[pipe_cmd->i][0]);
			if (execve(pipe_cmd->s, pipe_cmd->cmd[pipe_cmd->i], pipe_cmd->tab_env) == -1)
			{
				free(pipe_cmd->s);
				free_tab(pipe_cmd->tab_env);
				return (-2);
			}
		}
		else
		{
			wait(NULL);
			close(pipe_cmd->pfd[1]);
			pipe_cmd->fd_in = pipe_cmd->pfd[0];
			pipe_cmd->i++;
		}
	}
	free_tab(pipe_cmd->tab_env);
	return (0);
}

int		init_t_pipe(t_pipe_cmd *pipe_cmd, char **arg_list)
{
	if (!(pipe_cmd->tab_env = tablst(g_env)))
		return (0);
	pipe_cmd->len = ft_count_pipe(arg_list);
	pipe_cmd->cmd = prepare_cmd(arg_list, pipe_cmd->len);
	pipe_cmd->fd_in = 0;
	pipe_cmd->i = 0;
	pipe_cmd->ret_red = 0;
	return (1);
}

int    ft_pipe_2(char **arg_list)
{
	t_pipe_cmd	pipe_cmd;
	
	// init struct
	if (!init_t_pipe(&pipe_cmd, arg_list))
		return (0);
	loop_pipe(&pipe_cmd);
	return (1);
	// free ***cmd
}
