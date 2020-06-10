#include "../../incs/minishell.h"

int		builtin_exit(char **arg)
{
	int i;

	if (arg_len(arg) == 1)
	{
		ft_putstr("inside");
		//free_tab(arg);
		return (-1);
		exit(0);
	}
	if (arg_len(arg) > 2)
	{
		strerror(errno);
		free_tab(arg);
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