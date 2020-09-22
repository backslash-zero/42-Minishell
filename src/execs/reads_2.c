/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 00:53:51 by celestin          #+#    #+#             */
/*   Updated: 2020/09/22 14:37:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char			**tablst(t_list *lst)
{
	char	**ret;
	t_list	*tmp;
	int		i;

	ret = NULL;
	tmp = NULL;
	if (!(ret = malloc((ft_lstsize(lst) + 1) * sizeof(*ret))))
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (!(ret[i] = ft_strdup(tmp->content)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void			get_len_semic(char **arg, int *i, int *len_new_arg_list)
{
	*len_new_arg_list = 0;
	while (*i < arg_len(arg) && ft_strcmp(arg[*i], ";") != 0)
	{
		*len_new_arg_list += 1;
		*i += 1;
	}
}

void			check_signal(int status)
{
	if (WTERMSIG(status) == 3)
		ft_putstr("Quit: 3\n");
	if (WIFEXITED(status))
		g_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		g_print = 0;
		g_ret = 128 + WTERMSIG(status);
	}
	if (status == 2)
		g_print = 1;
}

int				ft_exec(char **arg_list)
{
	pid_t	proc;
	int		status;
	char	*s;
	char	**tab_env;

	if (!(tab_env = tablst(g_env)))
		return (-1);
	if ((proc = fork()) == -1)
	{
		free_tab(tab_env);
		return (-1);
	}
	if (proc == 0)
	{
		s = try_absolut_path(arg_list[0]);
		if (s != NULL && (ft_strcmp(s, "NOT_FOUND") == 0
		|| ft_strcmp(s, "IS_DIR") == 0))
		{
			free_tab(tab_env);
			if (ft_strcmp(s, "NOT_FOUND") == 0)
				exit(126);
			if (ft_strcmp(s, "IS_DIR") == 0)
				exit(127);
		}
		if (s == NULL)
			s = find_path_env(tab_env, arg_list[0]);
		if ((execve(s, arg_list, tab_env)) == -1)
		{
			free_tab(tab_env);
			if (errno == 13)
			{
				ft_strerror(s, NULL, arg_list[0], NULL);
				return (-3);
			}
			free(s);
			return (-2);
		}
	}
	else if (proc > 0)
	{
		if (!ft_strcmp(arg_list[0], "cat"))
			g_signal = 0;
		if (wait(&status) == -1)
		{
			free_tab(tab_env);
			ft_strerror(NULL, NULL, "wait", NULL);
			return (-1);
		}
		check_signal(status);
		if (g_ret == 127)
		{
			free_tab(tab_env);
			return (127);
		}
	}
	free_tab(tab_env);
	return (0);
}
