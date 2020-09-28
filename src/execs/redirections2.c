/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 15:56:23 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/26 15:27:28 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	redir_exec(char **arg_list, t_cmd *cmd, int fd, char **arg)
{
	int		ret_exec;

	if (!ft_checkbuiltins(arg_list, cmd))
	{
		ret_exec = ft_exec(arg_list);
		ft_printf_fd(2, "ret_exec in redir_exec00 = %d\n", ret_exec);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_printf_fd(2, "g_ret redir_exec= %d\n", g_ret);
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			free_tool(cmd->arg, cmd->input_arg, 0);
			free_tool(arg_list, arg, 1);
			close(fd);
			g_ret = 127;
			exit(127);
		}
	}
}

int		apply_redirections(char **arg, t_cmd *cmd, int fd)
{
	char	**arg_list;

	if (!(arg_list = deletebracket(arg)))
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (!arg_cleanup(arg_list))
	{
		free_tab(arg_list);
		return (ft_strerror(NULL, arg, NULL, NULL));
	}
	ft_printf_fd(2, "applyredirection before redir_exec\n");
	redir_exec(arg_list, cmd, fd, arg);
	ft_printf_fd(2, "g_ret apply_redirection = %d\n", g_ret);
	free_tab(arg_list);
	return (0);
}

int		r_anglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;

	fd = -1;
	cmd->apply_redir++;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		g_ret = 1;
		ft_error(NO_RIGHTS, NULL, NULL, name);
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

	fd = -1;
	cmd->apply_redir++;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		g_ret = 1;
		ft_error(NO_RIGHTS, NULL, NULL, name);
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

	fd = 0;
	cmd->apply_redir++;
	if ((fd = open(name, O_RDONLY, 0644)) == -1)
	{
		g_ret = 1;
		ft_error(NO_RIGHTS, NULL, NULL, name);
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
