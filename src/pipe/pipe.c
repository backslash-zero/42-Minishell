/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/03 16:54:00 by rzafari          ###   ########.fr       */
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
	printf("bonjour\n");
	while (pipe_cmd->cmd[pipe_cmd->i])
	{
		printf("while\n");
		pipe(pipe_cmd->pfd);
		printf("pipe\n");
		if ((pipe_cmd->proc = fork()) == -1)
		{
			printf("fork FAILED\n");
			free_tab(pipe_cmd->tab_env);
			return (-1);
		}
		else if (pipe_cmd->proc == 0)
		{
			printf("fils\n");
			dup2(pipe_cmd->fd_in, 0);
			printf("post\n");
			if (pipe_cmd->cmd[pipe_cmd->i + 1] != NULL)
				dup2(pipe_cmd->pfd[1], 1);
			printf("2\n");
			close(pipe_cmd->pfd[0]);
			printf("3\n");
			pipe_cmd->s = find_path_env(pipe_cmd->tab_env, pipe_cmd->cmd[pipe_cmd->i][0]);
			printf("END FILS\n");
			if (execve(pipe_cmd->s, pipe_cmd->cmd[pipe_cmd->i], pipe_cmd->tab_env) == -1)
			{
				free(pipe_cmd->s);
				free_tab(pipe_cmd->tab_env);
				return (-2);
			}

		}
		else
		{
			printf("daddy\n");
			wait(NULL);
			close(pipe_cmd->pfd[1]);
			pipe_cmd->fd_in = pipe_cmd->pfd[0];
			pipe_cmd->i++;
		}
	}
	free_tab(pipe_cmd->tab_env);
	return (0);
}

int		init_t_pipe(t_pipe_cmd pipe_cmd, char **arg_list)
{
	if (!(pipe_cmd.tab_env = tablst(g_env)))
		return (0);
	pipe_cmd.len = ft_count_pipe(arg_list);
	pipe_cmd.cmd = prepare_cmd(arg_list, pipe_cmd.len);
	pipe_cmd.fd_in = 0;
	pipe_cmd.i = 0;
	pipe_cmd.ret_red = 0;
	return (1);
}

int    ft_pipe_2(char **arg_list, t_parse *parse)
{
	t_pipe_cmd	pipe_cmd;
	
	(void)parse;
	// init struct
	if (!init_t_pipe(pipe_cmd, arg_list))
		return (0);
	loop_pipe(&pipe_cmd);
	return (1);
	// free ***cmd
}

void    ft_pipe(void)
{
	/* test */
	char *ls_str;
	char *wc_str;
	char *wc_ptr[2];
	char *ls_ptr[2];
	char *s;

	ls_str = "ls";
	wc_str = "wc";
	ls_ptr[1] = NULL;
	wc_ptr[1] = NULL;
	ls_ptr[0] = ls_str;
	wc_ptr[0] = wc_str;

	printtab(ls_ptr);
	printtab(wc_ptr);
	/* recuperer tab env */
	char	**tab_env;
	if (!(tab_env = tablst(g_env)))
		printf("g_env failed\n");
	printtab(tab_env);
	/* create the pipe */
   int  pfd[2];
   if (pipe(pfd) == -1)
		printf("pipe failed\n");
   /* create the child */
   int  pid;
   if ((pid = fork()) < 0)
		printf("fork failed\n");
	if (pid == 0)
	{
		/* child */
		s = find_path_env(tab_env, wc_str);
		close(pfd[1]); /* close the unused write side */
		dup2(pfd[0], 0); /* connect the read side with stdin */
		close(pfd[0]); /* close the read side */
		/* execute the process (wc command) */
		execve(s, wc_ptr, tab_env);
		// execlp("wc", "wc", (char *) 0);
		printf("wc failed"); /* if execlp returns, it's an error */
	}
	else
	{
       /* parent */
	   s = find_path_env(tab_env, ls_str);
       close(pfd[0]); /* close the unused read side */
       dup2(pfd[1], 1); /* connect the write side with stdout */
       close(pfd[1]); /* close the write side */
       /* execute the process (ls command) */
	   execve(s, ls_ptr, tab_env);
       // execlp("ls", "ls", (char *)0);
       printf("ls failed"); /* if execlp returns, it's an error */
	}
}
