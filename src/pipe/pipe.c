/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/25 00:50:26 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	pipe_dups(t_pipe_cmd *pipe_cmd)
{
	if (dup2(pipe_cmd->fd_in, 0) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (pipe_cmd->cmd[pipe_cmd->i + 1] != NULL)
	{
		if (dup2(pipe_cmd->pfd[1], 1) == -1)
		{
			ft_strerror(NULL, NULL, NULL, NULL);
			exit(errno);
		}
	}
	close(pipe_cmd->pfd[0]);
}

int		pipe_default(t_pipe_cmd *pipe_cmd, t_cmd *cmd, int *ret_exec)
{
	if (!arg_cleanup(pipe_cmd->cmd[pipe_cmd->i]))
		return (ft_strerror(NULL, pipe_cmd->cmd[pipe_cmd->i], NULL, NULL));
	if (!ft_checkbuiltins(pipe_cmd->cmd[pipe_cmd->i], cmd))
	{
		*ret_exec = ft_exec(pipe_cmd->cmd[pipe_cmd->i], cmd);
		if (*ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (*ret_exec == -45)
		{
			ft_error(NO_FILE, NULL, NULL,
						pipe_cmd->cmd[pipe_cmd->i][0]);
		}
		else if (*ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL,
						pipe_cmd->cmd[pipe_cmd->i][0]);
			return (-1);
		}
		else if (*ret_exec == 127 || *ret_exec == -3)
			return (-1);
	}
	return (0);
}

void	pipe_wait(int status, t_pipe_cmd *pipe_cmd)
{
	if (wait(&status) == -1)
		ft_strerror(NULL, NULL, "wait", NULL);
	check_signal(status);
	close(pipe_cmd->pfd[1]);
	pipe_cmd->fd_in = pipe_cmd->pfd[0];
	pipe_cmd->i++;
}

void	pipe_child(t_pipe_cmd *pipe_cmd, t_cmd *cmd, int *ret_exec)
{
	pipe_dups(pipe_cmd);
	if (check_redir(pipe_cmd->cmd[pipe_cmd->i]))
		redir_pipe(pipe_cmd->cmd[pipe_cmd->i], pipe_cmd, cmd);
	if (!pipe_cmd->check_redir)
	{
		if (pipe_default(pipe_cmd, cmd, ret_exec) == -1)
			free_and_exit(pipe_cmd, cmd, 0);
	}
	cmd->pipe_ret = g_ret;
	free_and_exit(pipe_cmd, cmd, g_ret);
}

int		loop_pipe(t_pipe_cmd *pipe_cmd, t_cmd *cmd)
{
	int ret_exec;
	int status;

	status = 0;
	while (pipe_cmd->cmd[pipe_cmd->i])
	{
		if (pipe_fork(pipe_cmd) == -1)
		{
			free_tab(pipe_cmd->tab_env);
			free_tab_3d(pipe_cmd->cmd);
			return (-1);
		}
		if (pipe_cmd->proc == 0)
			pipe_child(pipe_cmd, cmd, &ret_exec);
		else
			pipe_wait(status, pipe_cmd);
	}
	free_tab(pipe_cmd->tab_env);
	free_tab_3d(pipe_cmd->cmd);
	return (0);
}
