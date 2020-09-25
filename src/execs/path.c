/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:55:07 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/25 02:15:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	*check_paths(char **tab_env, char **arg_list)
{
	char *s;

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
	if (!s)
	{
		free_tab(tab_env);
		free(s);
		return (NULL);
	}
	return (s);
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
				return (arg);
			else if (ret_trypath == -21)
			{
				ft_strerror(arg, NULL, NULL, NULL);
				return ("IS_DIR");
			}
			else
			{
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
