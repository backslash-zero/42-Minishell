/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 21:34:01 by celestin          #+#    #+#             */
/*   Updated: 2020/09/21 23:43:19 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

void	toggle_redir(char **s, int i, t_pipe_cmd *pipe_cmd)
{
	if ((ft_strcmp(s[i], ">") == 0) ||
		(ft_strcmp(s[i], ">>") == 0) ||
		(ft_strcmp(s[i], "<") == 0))
	{
		pipe_cmd->check_redir = 1;
	}
}

void	redir_pipe(char **s, t_pipe_cmd *pipe_cmd, t_cmd *cmd)
{
	int	i;
	int	ret_red;

	i = 0;
	ret_red = 0;
	pipe_cmd->check_redir = 0;
	count_redir_pipe(s, cmd);
	while (s[i])
	{
		toggle_redir(s, i, pipe_cmd);
		if (ft_strcmp(s[i], ">") == 0)
			ret_red = r_anglebracket(s, cmd, s[i + 1]);
		else if (ft_strcmp(s[i], ">>") == 0)
			ret_red = r_dbanglebracket(s, cmd, s[i + 1]);
		else if (ft_strcmp(s[i], "<") == 0)
			ret_red = l_anglebracket(s, cmd, s[i + 1]);
		if (ret_red == -1)
			exit(1);
		i++;
	}
}
