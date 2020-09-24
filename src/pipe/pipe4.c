/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 20:52:27 by celestin          #+#    #+#             */
/*   Updated: 2020/09/24 23:08:03 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	free_and_exit(t_pipe_cmd *pipe_cmd, t_cmd *cmd, int exit_code)
{
	free_tab_3d(pipe_cmd->cmd);
	free_tool(cmd->arg, cmd->input_arg, 1);
	free_tab(pipe_cmd->tab_env);
	exit(exit_code);
}

int		ft_count_pipe(char **arg)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (arg[i])
	{
		if (!ft_strcmp(arg[i], "|"))
			count++;
		i++;
	}
	return (count);
}

int		check_redir(char **s)
{
	int	i;

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
	int	i;

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
