/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:42:59 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/22 09:38:28 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_ret	g_ret = 0;

int		is_forking(int val)
{
	static int is_forking = 0;

	if (val != 2)
		is_forking = val;
	return (is_forking);
}

void	signal_handler(int n)
{
	if (g_signal == 1)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\033[1C");
	}
	if (n == SIGINT)
	{

		if (g_print == 0)
		{
			ft_putchar('\n');
			print_prompt_prefix();
			g_print = 0;
		}
		g_ret = 1;
	}
	else if (n == SIGQUIT)
		g_ret = 0;
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_ret = 0;
	g_print = 0;
	if ((signal(SIGINT, signal_handler) == SIG_ERR))
	{
		ft_strerror(NULL, NULL, "signal", NULL);
		exit(1);
	}
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
	{
		ft_strerror(NULL, NULL, "signal", NULL);
		exit(1);
	}
	g_env = init_env(&g_env, envp);
	g_export = init_env(&g_export, envp);
	prompt();
	ft_lstclear(&g_env, free);
	ft_lstclear(&g_export, free);
	return (0);
}
