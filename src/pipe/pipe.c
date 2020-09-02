/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/02 17:03:22 by rzafari          ###   ########.fr       */
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

char	**ft_splitpipe_after(char **arg, int i)
{

}

char	**ft_splitpipe_before(char **arg, int i)
{

}

char		**cmd_arg(char **arg, int *i)
{
	int cmd_arg_len = 0;

	while (ft_strcmp(arg[cmd_arg_len], "|"))
		cmd_arg_len++;
	*i = cmd_arg_len;
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
			cmd[count] = cmd_arg(&arg_list[i], &i);
			i++;
		}
		else
		{
			cmd[count] = last_arg(&arg_list[i], &i);
			break ;
		}
		count++;
	}
	cmd[count] = NULL;
	return (cmd);
}

void    ft_pipe_2(char **arg_list)
{
	// preparer arg list dans un ***cmd
	int		pipe_len = ft_count_pipe(arg_list);
	char	***cmd = prepare_cmd(arg_list, pipe_len);
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
