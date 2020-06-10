#include "../incs/minishell.h"

// set_var(g_env, "PWD=", current_dir());

int		main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_env = init_env(&g_env, envp);
	prompt();
	ft_lstclear(&g_env, free);
	ft_lstclear(&g_export, free);
	// free env
	return (0);
}
