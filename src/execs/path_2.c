/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/21 18:50:32 by celestin          #+#    #+#             */
/*   Updated: 2020/09/21 18:59:46 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		try_path(char *s)
{
	struct stat file;

	errno = 0;
	stat(s, &file);
	if ((file.st_mode & S_IFMT) == S_IFDIR && (errno = EISDIR))
		return (-21);
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

char	*find_correct_path(char *s, char *arg)
{
	int		i;
	int		j;
	char	*test;
	char	*dup;

	i = -1;
	j = 0;
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
