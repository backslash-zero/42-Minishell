/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:01:55 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/17 11:04:52 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**deletebracket_next(char **arg, char **s)
{
	int	i;
	int j;

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
	return (deletebracket_next(arg, s));
}

void	count_redir(t_cmd *cmd)
{
	int i;

	i = 0;
	cmd->nb_redir = 0;
	cmd->apply_redir = 0;
	while (cmd->arg[i])
	{
		if (ft_strcmp(cmd->arg[i], ">") == 0 ||
		ft_strcmp(cmd->arg[i], ">>") == 0 || ft_strcmp(cmd->arg[i], "<") == 0)
			cmd->nb_redir++;
		i++;
	}
}

int		redirection(t_cmd *cmd)
{
	int	i;
	int ok;

	i = 0;
	cmd->redir_ok = 0;
	count_redir(cmd);
	while (cmd->arg[i])
	{
		if (ft_strcmp(cmd->arg[i], ">") == 0)
			if (r_anglebracket(cmd->arg, cmd, cmd->arg[i + 1]) == -1)
				return (-1);
		if (ft_strcmp(cmd->arg[i], ">>") == 0)
			if (r_dbanglebracket(cmd->arg, cmd, cmd->arg[i + 1]) == -1)
				return (-1);
		if (ft_strcmp(cmd->arg[i], "<") == 0)
			if (l_anglebracket(cmd->arg, cmd, cmd->arg[i + 1]) == -1)
				return (-1);
		i++;
	}
	if (cmd->redir_ok == 0)
		return (0);
	return (1);
}