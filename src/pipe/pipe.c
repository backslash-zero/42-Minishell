/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/02 14:03:41 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/02 14:59:21 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
