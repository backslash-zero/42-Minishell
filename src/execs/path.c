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

char	*check_paths_next(char **tab_env, char *s, char **arg_list)
{
	if (s == NULL)
		s = find_path_env(tab_env, arg_list[0]);
	if (!s)
	{
		free_tab(tab_env);
		free(s);
		return (NULL);
	}
	if (!ft_strcmp(s, "abcd"))
		free_tab(tab_env);
	return (s);
}

char	*check_paths(char **tab_env, char **arg_list, t_cmd *cmd)
{
	char *s;

	s = try_absolut_path(arg_list[0]);
	if (s != NULL && (ft_strcmp(s, "NOT_FOUND") == 0
		|| ft_strcmp(s, "IS_DIR") == 0))
	{
		(void)cmd;
		free_tab(tab_env);
		if (ft_strcmp(s, "NOT_FOUND") == 0)
		{
			free_tool(cmd->arg, cmd->input_arg, 1);
			exit(126);
		}
		if (ft_strcmp(s, "IS_DIR") == 0)
		{
			free_tool(cmd->arg, cmd->input_arg, 1);
			exit(127);
		}
	}
	return (check_paths_next(tab_env, s, arg_list));
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

char	*find_path_env_next(char **env, char *arg)
{
	int		i;
	int		j;
	char	*s;
	char	*path;

	i = -1;
	while (env[++i])
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
	return (NULL);
}

char	*find_path_env(char **env, char *arg)
{
	int		i;
	int		ok;

	i = -1;
	ok = 0;
	while (env[++i] && ok != 1)
	{
		if (ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")) == 0)
			ok = 1;
	}
	if (ok == 0)
		return (ft_strdup("abcd"));
	return (find_path_env_next(env, arg));
}
