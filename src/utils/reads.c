/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:07:50 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/02 17:04:10 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static void		print_gret(char *str)
{
	printf("%s		--	g_ret = %d\n", str, g_ret);
	int hey = 1;
}

void		printtab(char **tab)
{
	int i;

	i = 0;
	printf("len tab: %d\n", arg_len(tab));
	while (tab[i])
	{
		printf("str-%d: %s\n", i, tab[i]);
		i++;
	}
}

char			**tablst(t_list *lst)
{
	char	**ret;
	t_list	*tmp;
	int		i;

	ret = NULL;
	tmp = NULL;
	if (!(ret = malloc((ft_lstsize(lst) + 1) * sizeof(*ret))))
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (!(ret[i] = ft_strdup(tmp->content)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void			fd_dup(int i)
{
	static int input;
	static int output;

	if (i == 0)
	{
		input = dup(0);
		output = dup(1);
	}
	else if (i == 1)
	{
		dup2(input, 0);
		dup2(output, 1);
	}
}

int				launch_exec(char **arg, t_parse *parse, char **arg_list)
{
	int	ret_red;
	int	ret_exec;

	// print_gret("launch_exec_1");
	fd_dup(0);
	// print_gret("launch_exec_1.1");
	g_ret = 0;
	// print_gret("launch_exec_1.2");
	ret_red = redirection(arg_list, parse);
	// print_gret("launch_exec_2");
	if (!ret_red)
	{
		// print_gret("launch_exec_3");
		if (!ft_checkbuiltins(arg_list, parse))
		{
			// print_gret("launch_exec_4");
			ret_exec = ft_exec(arg_list);
			if (ret_exec == -1)
			{
				// print_gret("launch_exec_5");
				return (ft_strerror(NULL, NULL, "fork", NULL));
			}
			else if (ret_exec == -2)
			{
				ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
				// print_gret("launch_exec_6");
				return (-2);
			}
		}
		fd_dup(1);
		return (1);
	}
	if (ret_red == -1)
	{
		fd_dup(1);
		return (-1);
	}
	fd_dup(1);
	// print_gret("launch_exec_7");
	return (0);
}

void			check_signal(int status)
{
	if (WTERMSIG(status) == 3)
		ft_putstr("Quit\n");
	if (WIFEXITED(status))
		g_ret = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		g_ret = 128 + WTERMSIG(status);
}

int				ft_exec(char **arg_list)
{
	pid_t	proc;
	int		status;
	char	*s;
	char	**tab_env;

	if (!(tab_env = tablst(g_env)))
		return (-1);
	if ((proc = fork()) == -1)
	{
		free_tab(tab_env);
		return (-1);
	}
	if (proc == 0)
	{
		s = find_path_env(tab_env, arg_list[0]);
		printf("s = %s\n", s);
		int d = 0;
		while (arg_list[d])
		{
			printf("arg_list = %s\n", arg_list[d]);
			d++;
		}
		if ((execve(s, arg_list, tab_env)) == -1)
		{
			free(s);
			free_tab(tab_env);
			return (-2);
		}
	}
	else if (proc > 0)
	{
		if (wait(&status) == -1)
		{
			free_tab(tab_env);
			ft_strerror(NULL, NULL, "wait", NULL);
			return (-1);
		}
		check_signal(status);
	}
	free_tab(tab_env);
	return (0);
}

int				launch(char *input, t_parse *parse)
{
	char	**arg_list;
	char	**arg;
	int		i;
	int		len_new_arg_list;
	int		ret_exec;

	if (!(arg = parsing(input)))
		return (0);
	i = 0;
	while (arg[i] != NULL)
	{
		len_new_arg_list = 0;
		while (i < arg_len(arg) && ft_strcmp(arg[i], ";") != 0)
		{
			len_new_arg_list++;
			i++;
		}
		if ((arg_list = semicolon(arg, i, len_new_arg_list)) == NULL)
		{
			free_tab(arg_list);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		if (!check_g_ret_var(arg_list))
		{
			free_tab(arg_list);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		if (!cleanup_quotes(arg_list))
		{
			free_tab(arg_list);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		// print_gret("launch_2.1");
		if (arg_len(arg_list) == 1 && !ft_strcmp(arg_list[0], "pipe2"))
			ft_pipe_2(arg_list);
		else if (arg_len(arg_list) == 1 && !ft_strcmp(arg_list[0], "pipe"))
			ft_pipe();
		else
			ret_exec = launch_exec(arg, parse, arg_list);
		// print_gret("launch_2.2");
		if (ret_exec == -2)
			exit(127);
		// print_gret("launch_2.3");
		if (arg[i] == NULL)
		{
			free_tab(arg_list);
			break ;
		}
		// print_gret("launch_2.4");
		free_tab(arg_list);
		i++;
		// print_gret("launch_3");
	}
	free_tab(arg);
	// print_gret("launch_4");
	return (0);
}

void			prompt(void)
{
	char	buffer[MAX_INPUT_SIZE];
	int		ret;
	t_parse	parse;

	ft_builtinstab(&parse);
	while (1)
	{
		ret = 0;
		if (to_print == 0)
			print_prompt_prefix();
		if (to_print == 1)
			to_print = 0;
		ret = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
		if (ret == -1)
			exit(errno);
		if (ret)
			buffer[ret - 1] = '\0';
		else
			ft_strlcpy(buffer, "exit", 5);
		if (launch(buffer, &parse) == -1)
			return ;
	}
}
