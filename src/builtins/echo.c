#include "../../incs/minishell.h"

void		echo_print(char **arg, int i)
{
	while (arg[i])
	{
		if (arg[i][0] != '\0')
			ft_printf_fd(1 ,"%s", arg[i]);
		i++;
		if(arg[i])
			ft_putchar_fd(1, ' ');
	}
}

int		builtin_echo(char **arg)
{
	if (arg_len(arg) == 1)
	{
		ft_putchar_fd(1, '\n');
		return (1);
	}
	if (ft_strcmp(arg[1], "-n") == 0)
		echo_print(arg, 2);
	else
	{
		echo_print(arg, 1);
		ft_putchar_fd(1, '\n');
	}
	return(0);
}