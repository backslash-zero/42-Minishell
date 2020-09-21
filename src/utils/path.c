/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:55:07 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 16:22:51 by celestin         ###   ########.fr       */
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

char	*try_absolut_path(char *arg)
{
	int i;
	int ret_trypath;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == 47)
		{
			if ((ret_trypath = try_path(arg)) == 0)
			{
				return (arg);
			}
			else if (ret_trypath == -21)
			{
				ft_strerror(arg, NULL, NULL, NULL);
				return ("IS_DIR");
			}
			else
			{
				printf("not found\n");
				ft_error(NO_FILE, NULL, NULL, arg);
				return ("NOT_FOUND");
			}
		}
		i++;
	}
	return (NULL);
}

char	*find_path_env(char **env, char *arg)
{
	int		i;
	int		j;
	char	*s;
	char	*path;

	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")) == 0)
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			j++;
			s = ft_substr(env[i], j, ft_strlen(env[i]) - j);
			if ((path = find_correct_path(s, arg)) != NULL)
			{
				free(s);
				return (path);
			}
			free(s);
			free(path);
		}
	}
	return (NULL);
}
