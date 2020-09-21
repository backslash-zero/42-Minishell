/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:55:07 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/21 19:48:11 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
