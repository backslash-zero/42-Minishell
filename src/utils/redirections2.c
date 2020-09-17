/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:56:23 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/16 17:03:00 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		apply_redirections(char **arg, t_cmd *cmd, int fd)
{
	int		ret_exec;
	char	**arg_list;

	if (!(arg_list = deletebracket(arg)))
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (!ft_backslash(arg_list))
   	{
		free_tab(arg_list);
		return (ft_strerror(NULL, arg, NULL, NULL));
	}
	if (!ft_checkbuiltins(arg_list, cmd))
	{
		ret_exec = ft_exec(arg_list);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			free_tab(arg_list);
			close(fd);
			exit(127);
		}
	}
	free_tab(arg_list);
	return (0);
}

int		r_anglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;
	char	**arg_list;

	fd = -1;
	cmd->apply_redir++;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		g_ret = 1;
		ft_error(RNO_FILE, NULL, NULL, name);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
		if ((apply_redirections(arg, cmd, fd)) == -1)
			return (-1);
	cmd->redir_ok = 1;
	close(fd);
	return (1);
}

int		r_dbanglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;
	int		ret_exec;
	char	**arg_list;

	fd = -1;
	cmd->apply_redir++;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		g_ret = 1;
		ft_error(RNO_FILE, NULL, NULL, name);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
		if ((apply_redirections(arg, cmd, fd)) == -1)
			return (-1);
	cmd->redir_ok = 1;
	close(fd);
	return (1);
}

int		l_anglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;
	int		ret_exec;
	char	**arg_list;

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
		if ((apply_redirections(arg, cmd, fd)) == -1)
			return (-1);
	cmd->redir_ok = 1;
	close(fd);
	return (1);
}
