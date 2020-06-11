#include "../../incs/minishell.h"

int		builtin_exit(char **arg)
{
	int i;

	if (arg_len(arg) == 1)
	{
		free_tab(arg);
		return (-1);
		exit(0);
	}
	if (arg_len(arg) > 2)
	{
		free_tab(arg);
		strerror(errno);
		exit(0);
	}
	i = ft_atoi(arg[1]);
	if (i < 0)
	{
		free_tab(arg);
		exit (-i);
	}
	else
	{
		free_tab(arg);
		exit (i);
	}
}