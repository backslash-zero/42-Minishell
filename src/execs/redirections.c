/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:01:55 by rzafari           #+#    #+#             */
/*   Updated: 2020/10/02 02:04:04 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		check_perm(char *name)
{
	struct stat file;

	errno = 0;
	stat(name, &file);
	if (!(file.st_mode & S_IWOTH))
	{
		g_ret = 1;
		ft_error(NO_RIGHTS, NULL, NULL, name);
		return (-1);
	}
	return (0);
}

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

	if (!find_first_redir(cmd))
		return (0);
	i = 0;
	cmd->redir_ok = 0;
	count_redir(cmd);
	if (!sort_2(cmd))
		return (-1);
	if (!sort_redir(cmd))
		return (-1);
	while (cmd->arg[i])
	{
		if (check_if_ranglebracket(cmd, i) == -1)
			return (-1);
		if (check_if_dbanglebracket(cmd, i) == -1)
			return (-1);
		if (check_if_langlebracket(cmd, i) == -1)
			return (-1);
		i++;
	}
	if (cmd->redir_ok == 0)
		return (0);
	return (1);
}
