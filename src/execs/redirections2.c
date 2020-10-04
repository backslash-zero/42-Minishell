/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:56:23 by rzafari           #+#    #+#             */
/*   Updated: 2020/10/02 02:02:08 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	redir_exec(char **arg_list, t_cmd *cmd, int fd, t_pipe_cmd *pipe_cmd)
{
	int		ret_exec;

	if (!ft_checkbuiltins(arg_list, cmd))
	{
		ret_exec = ft_exec(arg_list, cmd);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			free_tool(cmd->arg, cmd->input_arg, 1);
			free_tab(arg_list);
			if (pipe_cmd != NULL && pipe_cmd->len > 0)
			{
				free_tab_3d(pipe_cmd->cmd);
				free_tab(pipe_cmd->tab_env);
			}
			close(fd);
			exit(127);
		}
	}
}

int		apply_redirections(char **arg, t_cmd *cmd, int fd, t_pipe_cmd *pipe_cmd)
{
	char	**arg_list;
	//int		ret;
	if (!(arg_list = deletebracket(arg)))
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
/*	if ((ret = arg_cleanup(arg_list)) < 1)
	{
		free_tab(arg_list);
		free(arg);
		if (!ret)
			return (ft_strerror(NULL, NULL, NULL, NULL));
		else
			return (-1);
	}*/
	redir_exec(arg_list, cmd, fd, pipe_cmd);
	free_tab(arg_list);
	return (0);
}

int		r_anglebracket(char **arg, t_cmd *cmd, char *name, t_pipe_cmd *pipe_cmd)
{
	int		fd;

	fd = -1;
	cmd->apply_redir++;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		if (check_perm(name) == -1)
			return (-1);
		g_ret = 1;
		ft_error(NO_FILE, NULL, NULL, name);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
		if ((apply_redirections(arg, cmd, fd, pipe_cmd)) == -1)
			return (-1);
	cmd->redir_ok = 1;
	close(fd);
	return (1);
}

int		r_dbanglebracket(char **arg, t_cmd *cmd, char *name,
t_pipe_cmd *pipe_cmd)
{
	int		fd;

	fd = -1;
	cmd->apply_redir++;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		if (check_perm(name) == -1)
			return (-1);
		g_ret = 1;
		ft_error(NO_FILE, NULL, NULL, name);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
		if ((apply_redirections(arg, cmd, fd, pipe_cmd)) == -1)
			return (-1);
	cmd->redir_ok = 1;
	close(fd);
	return (1);
}

int		l_anglebracket(char **arg, t_cmd *cmd, char *name, t_pipe_cmd *pipe_cmd)
{
	int		fd;

	fd = 0;
	cmd->apply_redir++;
	if ((fd = open(name, O_RDONLY, 0644)) == -1)
	{
		g_ret = 1;
		ft_error(NO_FILE, NULL, NULL, name);
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
		if ((apply_redirections(arg, cmd, fd, pipe_cmd)) == -1)
			return (-1);
	cmd->redir_ok = 1;
	close(fd);
	return (1);
}
