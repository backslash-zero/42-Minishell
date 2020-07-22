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
	if (n == SIGINT)
	{
		ft_putstr("\n");
		print_prompt_prefix();
		g_ret = 130;
	}
	else if (n == SIGQUIT)
	{
		ft_putstr("\033[1C");
		ft_putstr("\b\b \b\b \b\b");
		ft_putstr("\033[1C");
		g_ret = 131;
	}
}

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	g_ret = 0;
	if (signal(SIGINT, signal_handler) == SIG_ERR)
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
