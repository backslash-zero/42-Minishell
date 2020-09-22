/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:07:50 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/22 11:16:31 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			fd_dup(int i)
{
	static int input;
	static int output;

	if (i == 0)
	{
		if ((input = dup(0)) == -1 || (output = dup(1)) == -1)
		{
			ft_strerror(NULL, NULL, NULL, NULL);
			exit(errno);
		}
	}
	else if (i == 1)
	{
		if (dup2(input, 0) == -1 || dup2(output, 1) == -1)
		{
			ft_strerror(NULL, NULL, NULL, NULL);
			exit(errno);
		}
	}
}

int				launch_exec(char **arg, t_cmd *cmd)
{
	int	ret_red;
	int	ret_exec;

	fd_dup(0);
	ret_red = redirection(cmd);
	if (!ret_red)
	{
		if (!arg_cleanup(cmd->arg))
		{
			free_tab(cmd->arg);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		if (!ft_checkbuiltins(cmd->arg, cmd))
		{
			ret_exec = ft_exec(cmd->arg);
			if (ret_exec == -1)
				return (ft_strerror(NULL, NULL, "fork", NULL));
			else if (ret_exec == -2)
			{
				ft_error(CMD_NOT_FOUND, NULL, NULL, cmd->arg[0]);
				return (-2);
			}
			else if (ret_exec == -3)
				return (-2);
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
	return (0);
}

int				launch(char *input, t_cmd *cmd)
{
	char	**arg;
	int		i;
	int		len_new_arg_list;
	int		ret_exec;

	if (!(arg = parsing(input)))
		return (0);
	i = 0;
	while (arg[i] != NULL)
	{
		//get_len_semic(arg, &i, &len_new_arg_list);
		len_new_arg_list = 0;
		while (i < arg_len(arg) && ft_strcmp(arg[i], ";") != 0)
		{
			len_new_arg_list++;
			i++;
		}
		if ((cmd->arg = semicolon(arg, i, len_new_arg_list)) == NULL)
		{
			free_tab(cmd->arg);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		if (ft_count_pipe(cmd->arg) > 0)
		{
			ret_exec = ft_pipe_2(cmd->arg, cmd);
			if (ret_exec == -1)
				g_ret = 127;
		}
		else
			ret_exec = launch_exec(arg, cmd);
		if (ret_exec == -2)
			exit(127);
		if (arg[i] == NULL)
			break ;
		i++;
	}
	return (0);
}

void			prompt(void)
{
	char	buffer[MAX_INPUT_SIZE];
	int		ret;
	t_cmd	cmd;

	ft_builtinstab(&cmd);
	g_signal = 1;
	while (1)
	{
		ret = 0;
		if (g_print == 0)
			print_prompt_prefix();
		if (g_print == 1)
			g_print = 0;
		if (g_signal == 0)
			g_signal = 1;
		ret = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
		if (ret == -1)
			exit(errno);
		if (ret)
		{
			while (buffer[ret - 1] != '\n')
			{
				ft_putstr("\033[2C\b\b  \033[2D");
				ret += read(STDIN_FILENO, &buffer[ret], MAX_INPUT_SIZE);
			}
			buffer[ret - 1] = '\0';
		}
		else
			ft_strlcpy(buffer, "exit", 5);
		if (launch(buffer, &cmd) == -1)
			return ;
	}
}
