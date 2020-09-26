/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 00:53:51 by celestin          #+#    #+#             */
/*   Updated: 2020/09/26 16:30:56 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int				ft_exec_father(char **tab_env, char **arg_list)
{
	int		status;

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
	return (0);
}

int				ft_exec_child(char **tab_env, char **arg_list)
{
	char *s;

	if (!(s = check_paths(tab_env, arg_list)))
		return (-2);
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
	return (0);
}

int				launch_ft_exec(t_cmd *cmd)
{
	int	ret_exec;

	ret_exec = ft_exec(cmd->arg);
	if (ret_exec == -1)
		return (ft_strerror(NULL, NULL, "fork", NULL));
	else if (ret_exec == -2)
	{
		ft_error(CMD_NOT_FOUND, NULL, NULL, cmd->arg[0]);
		return (-2);
	}
	else if (ret_exec == -3)
		return (-2);
	return (ret_exec);
}

int				launch_exec(char **arg, t_cmd *cmd)
{
	int	ret_red;
	int	ret_exec;

	fd_dup(0);
	ret_red = redirection(cmd);
	if (!ret_red)
	{
		if (!arg_cleanup(cmd->arg))
		{
			free_tab(cmd->arg);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		if (!ft_checkbuiltins(cmd->arg, cmd))
		{
			if ((ret_exec = launch_ft_exec(cmd)) != 0)
				return (ret_exec);
		}
		return (dup_return(1));
	}
	if (ret_red == -1)
		return (dup_return(1));
	return (dup_return(0));
}

int				ft_exec(char **arg_list)
{
	pid_t	proc;
	int		ret_exec;
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
		if ((ret_exec = ft_exec_child(tab_env, arg_list)) != 0)
			return (ret_exec);
	}
	else if (proc > 0)
	{
		if ((ret_exec = ft_exec_father(tab_env, arg_list)) != 0)
			return (ret_exec);
	}
	free_tab(tab_env);
	return (0);
}
