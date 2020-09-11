/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/11 13:13:08 by rzafari          ###   ########.fr       */
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

char		**cmd_arg_get(char **arg, int *i, t_pipe_cmd *pipe_cmd)
{
	int cmd_arg_len = 0;
	int j;
	char **cmd_arg;

	j = 0;
	while (ft_strcmp(arg[cmd_arg_len], "|"))
		cmd_arg_len++;
	*i += cmd_arg_len;
	if (!(cmd_arg = malloc(sizeof(char*) * cmd_arg_len + 1)))
		return (NULL);
	while (j < cmd_arg_len)
	{
		cmd_arg[j] = ft_strdup(arg[j]);
		j++;
	}
	cmd_arg[j] = NULL;
	return (cmd_arg);
}

char		**last_cmd_arg(char **arg, t_pipe_cmd *pipe_cmd)
{
	int len = 0;
	int j;
	char **cmd_arg;

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

char		***prepare_cmd(char **arg_list, t_pipe_cmd *pipe_cmd) //int pipe_len)
{
	char ***cmd;
	int i = 0;
	int cmd_arg = 0;
	int count = 0;

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

int check_redir(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0 || ft_strcmp(s[i], ">>") == 0 ||
		ft_strcmp(s[i], "<") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	count_redir_pipe(char **s, t_cmd *cmd)
{
	int i;

	i = 0;
	cmd->nb_redir = 0;
	cmd->apply_redir = 0;
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0 || ft_strcmp(s[i], ">>") == 0 ||
		ft_strcmp(s[i], "<") == 0)
			cmd->nb_redir++;
		i++;
	}
}

void	redir_pipe(char **s, t_pipe_cmd *pipe_cmd, t_cmd *cmd)
{
	int i;

	i = 0;
	pipe_cmd->check_redir = 0;
	count_redir_pipe(s, cmd);
	while (s[i])
	{
		if (ft_strcmp(s[i], ">") == 0)
		{
			cmd->apply_redir++;
			r_anglebracket(s, cmd, s[i + 1]);
			pipe_cmd->check_redir = 1;
		}
		else if (ft_strcmp(s[i], ">>") == 0)
		{
			cmd->apply_redir++;
			r_dbanglebracket(s, cmd, s[i + 1]);
			pipe_cmd->check_redir = 1;
		}
		else if (ft_strcmp(s[i], "<") == 0)
		{
			cmd->apply_redir++;
			l_anglebracket(s, cmd, s[i + 1]);
			pipe_cmd->check_redir = 1;
		}
		i++;
	}
}

int		loop_pipe(t_pipe_cmd *pipe_cmd, t_cmd *cmd)
{
	int ret_exec;
	int status;
	
	while (pipe_cmd->cmd[pipe_cmd->i])
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
		else if (pipe_cmd->proc == 0)
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
			if (check_redir(pipe_cmd->cmd[pipe_cmd->i]))
				redir_pipe(pipe_cmd->cmd[pipe_cmd->i],pipe_cmd, cmd);
			if (!pipe_cmd->check_redir)
			{
				ret_exec = ft_exec(pipe_cmd->cmd[pipe_cmd->i]);
				if (ret_exec == -1)
					ft_strerror(NULL, NULL, "fork", NULL);
				else if (ret_exec == -2)
				{
					ft_error(CMD_NOT_FOUND, NULL, NULL, pipe_cmd->cmd[pipe_cmd->i][0]);
					exit(127);
				}
				else if (ret_exec == 127)
					exit(127);
			}
			exit (0);
		}
		else
		{
			if (wait(&status) == -1)
				ft_strerror(NULL, NULL, "wait", NULL);
			check_signal(status);
			close(pipe_cmd->pfd[1]);
			pipe_cmd->fd_in = pipe_cmd->pfd[0];
			pipe_cmd->i++;
		}
	}
	free_tab(pipe_cmd->tab_env);
	free_tab_3d(pipe_cmd->cmd);
	return (0);
}

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

int    ft_pipe_2(char **arg_list, t_cmd *cmd)
{
	t_pipe_cmd	pipe_cmd;
	
	if (!init_t_pipe(&pipe_cmd, arg_list))
		return (0);
	loop_pipe(&pipe_cmd, cmd);
	if (g_ret == 127)
		return (-1);
	return (0);
}
