/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 11:41:16 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/18 08:28:52 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char *find_pwd_env(char **env)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")) == 0)
		{
			j = 0;
			while (env[i][j] != '=')
				j++;
			j++;
			s = ft_substr(env[i], j, ft_strlen(env[i]) - j);
			return (s);
		}
		i++;
	}
	return (NULL);
}

int		builtin_pwd(char **arg)
{
	char *dir;
	char **env;

	dir = NULL;
	(void)arg;
	if (arg_len(arg) > 1)
		return (ft_error(PWD_MANY_ARGS, NULL, NULL, NULL));
	if (!(dir = getcwd(dir, 0)))
	{
		if (!(env = tablst(g_env)))
			return (-1);
		dir = find_pwd_env(env);
		if (dir == NULL)
			return (ft_strerror(NULL, NULL, NULL, NULL));
		free_tab(env);
	}
	ft_putstr_fd(1, dir);
	ft_putchar_fd(1, '\n');
	free(dir);
	return (0);
}
