/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 14:07:50 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/25 00:51:18 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void			fd_dup(int i)
{
	static int input;
	static int output;

	if (i == 0)
	{
		if ((input = dup(0)) == -1)
		{
			ft_strerror(NULL, NULL, NULL, NULL);
			exit(errno);
		}
		if ((output = dup(1)) == -1)
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

int				dup_return(int value)
{
	fd_dup(1);
	return(value);
}

void			init_prompt(int *ret, char *buffer)
{
	*ret = 0;
	if (g_print == 0)
		print_prompt_prefix();
	if (g_print == 1)
		g_print = 0;
	if (g_signal == 0)
		g_signal = 1;
	*ret = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
	if (*ret == -1)
		exit(errno);
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
		init_prompt(&ret, buffer);
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
