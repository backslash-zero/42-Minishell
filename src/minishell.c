#include "../incs/minishell.h"

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_env = init_env(&g_env, envp);
	g_export = init_env(&g_export, envp);
	prompt();
	ft_lstclear(&g_env, free);
	ft_lstclear(&g_export, free);
 	return (0);
}
