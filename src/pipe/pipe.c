/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/22 11:35:56 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		pipe_fork(t_pipe_cmd *pipe_cmd)
{
	if (pipe(pipe_cmd->pfd) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if ((pipe_cmd->proc = fork()) == -1)
	{
		free_tab(pipe_cmd->tab_env);
		free_tab_3d(pipe_cmd->cmd);
		return (-1);
	}
	return (0);
}

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
		*ret_exec = ft_exec(pipe_cmd->cmd[pipe_cmd->i]);
		printf("ret_exec = %d\n", *ret_exec);
		ft_printf_fd(2,"ret_exec = %d\n", *ret_exec);
		if (*ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (*ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL,
						pipe_cmd->cmd[pipe_cmd->i][0]);
			ft_printf_fd(2,"pipe_default00\n");
			free_tab_3d(pipe_cmd->cmd);
			ft_printf_fd(2,"pipe_default01\n");
			return (-1);
			//exit(127);
		}
		else if (*ret_exec == 127 || *ret_exec == -3)
			exit(127);
	}
	ft_printf_fd(2,"pipe_default03\n");
	free_tab_3d(pipe_cmd->cmd);
	ft_printf_fd(2,"pipe_default04\n");
	return (0);
}

void	pipe_wait(int status, t_pipe_cmd *pipe_cmd)
{
	if (wait(&status) == -1)
		ft_strerror(NULL, NULL, "wait", NULL);
	check_signal(status);
	close(pipe_cmd->pfd[1]);
	ft_printf_fd(2, "pipe_wait00\n");	
	pipe_cmd->fd_in = pipe_cmd->pfd[0];
	pipe_cmd->i++;
}

int		loop_pipe(t_pipe_cmd *pipe_cmd, t_cmd *cmd)
{
	int ret_exec;
	int status;

	while (pipe_cmd->cmd[pipe_cmd->i])
	{
		if (pipe_fork(pipe_cmd) == -1)
			return (-1);
		if (pipe_cmd->proc == 0)
		{
			pipe_dups(pipe_cmd);
			if (check_redir(pipe_cmd->cmd[pipe_cmd->i]))
			{
				redir_pipe(pipe_cmd->cmd[pipe_cmd->i], pipe_cmd, cmd);
				free_tab_3d(pipe_cmd->cmd);
			}
			if (!pipe_cmd->check_redir)
			{
				if (pipe_default(pipe_cmd, cmd, &ret_exec) == -1)
				{
					printf("loop_pipe04\n");
					ft_printf_fd(2,"loop_pipe04\n");
					exit(0);
				}
			}
			cmd->pipe_ret = g_ret;
			exit(g_ret);
		}
		else
			pipe_wait(status, pipe_cmd);
	}
	free_tab(pipe_cmd->tab_env);
	printf("loop_pipe01\n");
	free_tab_3d(pipe_cmd->cmd);
	printf("loop_pipe end\n");
	return (0);
}
