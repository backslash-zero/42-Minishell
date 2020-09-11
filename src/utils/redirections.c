/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:01:55 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/11 11:51:11 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**deletebracket(char **arg)
{
	int		i;
	int		j;
	char	**s;

	i = 0;
	j = 0;
	while (arg[i] != NULL && (ft_strcmp(arg[i], ">")) != 0 &&
	(ft_strcmp(arg[i], ">>")) != 0)
	{
		if ((ft_strcmp(arg[i], "<")) != 0)
			j++;
		i++;
	}
	if (!(s = (char **)malloc(sizeof(char *) * (j + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (arg[i] != NULL && (ft_strcmp(arg[i], ">")) != 0 &&
	(ft_strcmp(arg[i], ">>")) != 0 && (ft_strcmp(arg[i], "<")) != 0)
	{
		if ((s[j] = ft_strdup(arg[i])) == NULL)
		{
			free_tab(s);
			return (NULL);
		}
		j++;
		i++;
	}
	s[j] = NULL;
	return (s);
}

int		r_anglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;
	int		ret_exec;
	char	**arg_list;

	fd = -1;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
	{
		if (!(arg_list = deletebracket(arg)))
		{
			close(fd);
			ft_strerror(NULL, NULL, NULL, NULL);
			return (-1);
		}
		if (!ft_checkbuiltins(arg_list, cmd))
		{
			ret_exec = ft_exec(arg_list);
			if (ret_exec == -1)
				ft_strerror(NULL, NULL, "fork", NULL);
			else if (ret_exec == -2)
			{
				ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
				free(arg_list);
				close(fd);
				exit(127);
			}
		}
		free_tab(arg_list);
	}
	close(fd);
	return (1);
}

int		r_dbanglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;
	int		ret_exec;
	char	**arg_list;

	fd = -1;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		exit(errno);
	}
	if (cmd->apply_redir == cmd->nb_redir)
	{
		if ((arg_list = deletebracket(arg)) == NULL)
		{
			close(fd);
			ft_strerror(NULL, NULL, NULL, NULL);
			return (-1);
		}
		if (!ft_checkbuiltins(arg_list, cmd))
		{
			ret_exec = ft_exec(arg_list);
			if (ret_exec == -1)
				ft_strerror(NULL, NULL, "fork", NULL);
			else if (ret_exec == -2)
			{
				ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
				free(arg_list);
				close(fd);
				exit(127);
			}
		}
		free(arg_list);
	}
	close(fd);
	return (1);
}

int		l_anglebracket(char **arg, t_cmd *cmd, char *name)
{
	int		fd;
	int		l;
	int		ret_exec;
	char	**arg_list;

	l = 0;
	fd = 0;
	if (l == arg_len(arg))
	{
		if ((fd = open(name, O_RDONLY, 0644)) == -1)
		{
			g_ret = 1;
			ft_strerror(NULL, NULL, NULL, NULL);
			return (-1);
		}
		if (dup2(fd, 0) == -1)
		{
			ft_strerror(NULL, NULL, NULL, NULL);
			exit(errno);
		}
	}
	if ((arg_list = deletebracket(arg)) == NULL)
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (!ft_checkbuiltins(arg_list, cmd))
	{
		ret_exec = ft_exec(arg_list);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			close(fd);
			exit(127);
		}
		close (fd);
	}
	close(fd);
	free_tab(arg_list);
	return (1);
}

void	count_redir(t_cmd *cmd)
{
	int i;

	i = 0;
	cmd->nb_redir = 0;
	cmd->apply_redir = 0;
	while (cmd->arg[i])
	{
		if (ft_strcmp(cmd->arg[i], ">") == 0 || ft_strcmp(cmd->arg[i], ">>") == 0 ||
		ft_strcmp(cmd->arg[i], "<") == 0)
			cmd->nb_redir++;
		i++;
	}
}

int		redirection(t_cmd *cmd)
{
	int	i;
	int ok;

	i = 0;
	ok = 0;
	count_redir(cmd);
	while (cmd->arg[i])
	{
		if (ft_strcmp(cmd->arg[i], ">") == 0)
		{
			ok = 1;
			cmd->apply_redir++;
			if (r_anglebracket(cmd->arg, cmd, cmd->arg[i + 1]) == -1)
				return (-1);
		}
		else if (ft_strcmp(cmd->arg[i], ">>") == 0)
		{
			ok = 1;
			cmd->apply_redir++;
			if (r_dbanglebracket(cmd->arg, cmd, cmd->arg[i + 1]) == -1)
				return (-1);
		}
		else if (ft_strcmp(cmd->arg[i], "<") == 0)
		{
			ok = 1;
			cmd->apply_redir++;
			if (l_anglebracket(cmd->arg, cmd, cmd->arg[i + 1]) == -1)
				return (-1);
		}
		i++;
	}
	if (ok == 0)
		return (0);
	return (1);
}
