/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/08 12:17:27 by rzafari          ###   ########.fr       */
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

char		**last_cmd_arg(char **arg, t_pipe_cmd *pipe_cmd)
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
	j = 0;
	while (cmd_arg[j])
	{
		printf("cmd_arg00[%d] = %s\n", j, cmd_arg[j]);
		j++;
	}
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
	printf("redir_flag = %d\n", pipe_cmd->chec_redir);
	return (cmd);
}

int check_redir(char **s)
{
	int i;

	i = 0;
	printf("im in check_redir\n");
	while (s[i])
	{
		printf("s = %s\n", s[i]);
		//if (ft_strcmp(s[i], ">") == 0 && ft_strcmp(s[i], ">>") &&
		//ft_strcmp(s[i], "<") == 0)
	//		return (1);
		i++;
	}
	return (0);
}

void	r_bracket(char *name, t_pipe_cmd *pipe_cmd)
{
	if ((pipe_cmd->fd_redir = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
	}
	dup2(pipe_cmd->fd_redir, 1);
}

void	dr_bracket(char *name, t_pipe_cmd *pipe_cmd)
{
	if ((pipe_cmd->fd_redir = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
	}
	dup2(pipe_cmd->fd_redir, 1);
}

void	l_bracket(char *name, t_pipe_cmd *pipe_cmd)
{
	if ((pipe_cmd->fd_redir = open(name, O_RDONLY)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
	}
	dup2(pipe_cmd->fd_redir, 0);
}

void	redir_pipe(char **s, t_pipe_cmd *pipe_cmd)
{
	int i;

	i = 0;
	while (s[i])
	{
		printf("s = %s\n", s[i]);
		if (ft_strcmp(s[i], ">") == 0)
		{
			printf("i found the right redirection\n");
			r_bracket(s[i + 1], pipe_cmd);
		}
		else if (ft_strcmp(s[i], ">>") == 0)
			dr_bracket(s[i + 1], pipe_cmd);
		else if (ft_strcmp(s[i], "<") == 0)
			l_bracket(s[i + 1], pipe_cmd);
		close(pipe_cmd->fd_redir);
		i++;
	}
}

int		loop_pipe(t_pipe_cmd *pipe_cmd)
{
	//int l = 0;
	int k;
	/*while (pipe_cmd->cmd[l])
	{
		k = 0;
		while(pipe_cmd->cmd[l][k])
		{
			printf("cmd = %s\n", pipe_cmd->cmd[l][k]);
			k++;
		}
		printf("\n");
		l++;
	}*/
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
			k = 0;
			while(pipe_cmd->cmd[pipe_cmd->i][k])
			{
				printf("cmd = %s\n", pipe_cmd->cmd[pipe_cmd->i][k]);
				k++;
			}
			printf("\n");
			// check redirection + open file + assign to struct + t_pipe_cmd_2_t_cmd
			dup2(pipe_cmd->fd_in, 0);
			if (pipe_cmd->cmd[pipe_cmd->i + 1] != NULL)
				dup2(pipe_cmd->pfd[1], 1);
			close(pipe_cmd->pfd[0]);
			printf("i = %d\n", pipe_cmd->i);
			if (check_redir(pipe_cmd->cmd[pipe_cmd->i]))
			{
				printf("lolilol\n");
				redir_pipe(pipe_cmd->cmd[pipe_cmd->i],pipe_cmd);
			}
			printf("lolilol_01\n");
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
	pipe_cmd->chec_redir = 0;
	pipe_cmd->len = ft_count_pipe(arg_list);
	pipe_cmd->cmd = prepare_cmd(arg_list, pipe_cmd);
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
