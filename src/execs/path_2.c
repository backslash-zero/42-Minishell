/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:50:32 by celestin          #+#    #+#             */
/*   Updated: 2020/09/25 01:31:25 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

int		try_path(char *s)
{
	struct stat file;

	errno = 0;
	if (stat(s, &file) != -1)
	{
		if ((file.st_mode & S_IFMT) == S_IFDIR && (errno = EISDIR))
			return (-21);
	}
	if (errno)
		return (-1);
	return (0);
}

char	*catch_path(char *test, char *arg)
{
	char *dup;

	if ((dup = ft_strjoin(test, arg)) == NULL)
	{
		free(test);
		return (NULL);
	}
	free(test);
	return (dup);
}

void	init_find_correct_path(int *i, int *j)
{
	*i = -1;
	*j = 0;
}

char	*find_correct_path(char *s, char *arg)
{
	int		i;
	int		j;
	char	*test;
	char	*dup;

	init_find_correct_path(&i, &j);
	dup = NULL;
	if (!ft_strchr(s, ':'))
		return (NULL);
	while (s[++i])
	{
		if (s[i] == ':' || s[i + 1] == '\0')
		{
			i = (s[i + 1] == '\0') ? i++ : i;
			if ((test = ft_strldup(s, j, i - 1)) == NULL)
				return (NULL);
			if ((dup = catch_path(test, arg)) == NULL)
				return (NULL);
			if (!try_path(dup))
				return (dup);
			free(dup);
			j = i + 1;
		}
	}
	return (NULL);
}
