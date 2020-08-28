/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:01:55 by rzafari           #+#    #+#             */
/*   Updated: 2020/08/28 13:56:17 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

int		permission_check(int fd)
{
	struct stat buff;

	if ((fstat(fd, &buff) == -1))
	{
		g_ret = 126;
		return (-1);
	}
	if (buff.st_mode >= 32896)
	{
		ft_printf_fd(3, "buff.st_mode = %d\n", buff.st_mode);
		return (1);
	}
	return (0);
}

int		r_anglebracket(char **arg, t_parse *parse, char *name)
{
	int		fd;
	int		ret_exec;
	char	**arg_list;

	fd = -1;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	dup2(fd, 1);
	if (!(arg_list = deletebracket(arg)))
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (!ft_checkbuiltins(arg_list, parse))
	{
		ret_exec = ft_exec(arg_list);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			close(fd);
			exit(127);
		}
	}
	close(fd);
	return (1);
}

int		r_dbanglebracket(char **arg, t_parse *parse, char *name)
{
	int		i;
	int		fd;
	int		ret_exec;
	char	**arg_list;

	i = 0;
	fd = -1;
	if ((fd = open(name, O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	dup2(fd, 1);
	if ((arg_list = deletebracket(arg)) == NULL)
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	if (!ft_checkbuiltins(arg_list, parse))
	{
		ret_exec = ft_exec(arg_list);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			close(fd);
			exit(127);
		}
	}
	close(fd);
	free(arg_list);
	return (1);
}

int		l_anglebracket(char **arg, t_parse *parse, char *name)
{
	int		i;
	int		fd;
	int		l;
	int		ret_exec;
	char	**arg_list;

	i = 0;
	//l = 0;
	//printf("im in l\n");
	/*while (arg[l])
	{
		if (ft_strcmp(arg[l], ">") == 0 || ft_strcmp(arg[l], ">>") == 0)
		{
			l++;
			name = arg[l];
			break ;
		}
		l++;
	}*/
	//printf("name = %s\n", name);
	if ((fd = open(name, O_RDONLY, 0644)) == -1)
	{
		g_ret = 1;
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	dup2(fd, 0);
	if ((arg_list = deletebracket(arg)) == NULL)
	{
		close(fd);
		ft_strerror(NULL, NULL, NULL, NULL);
		return (-1);
	}
	/*int s = 0;
	while (arg_list[s])
	{
		ft_printf_fd(3, "arg = %s\n", arg_list[s]);
		s++;
	}*/
	if (!ft_checkbuiltins(arg_list, parse))
	{
		//printf("ok\n");
		ret_exec = ft_exec(arg_list);
		if (ret_exec == -1)
			ft_strerror(NULL, NULL, "fork", NULL);
		else if (ret_exec == -2)
		{
			ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			close(fd);
			exit(127);
		}
		close (fd);
	}
	close(fd);
	return (1);
}

int		redirection(char **arg, t_parse *parse)
{
	int	i;
	int ok = 0;

	i = 0;
	while (arg[i])
	{
		//printf("redirect => arg = %s\n", arg[i]);
		if (ft_strcmp(arg[i], ">") == 0)
		{
			ok = 1;
			if (r_anglebracket(arg, parse, arg[i + 1]) == -1)
				return (-1);
		}
		else if (ft_strcmp(arg[i], ">>") == 0)
		{
			ok = 1;
			if (r_dbanglebracket(arg, parse, arg[i + 1]) == -1)
				return (-1);
		}
		else if (ft_strcmp(arg[i], "<") == 0)
		{
			ok = 1;
			if (l_anglebracket(arg, parse, arg[i + 1]) == -1)
				return (-1);
		}
		i++;
	}
	if (ok == 0)
		return (0);
	else
		return (1);
}
