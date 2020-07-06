#include "../../incs/minishell.h"

void		echo_print(char **arg, int i, int fd)
{
	while (arg[i])
	{
		ft_printf_fd(fd ,"%s", arg[i]);
		//ft_putstr_fd(fd, arg[i]);
		i++;
		if(arg[i])
			ft_putchar_fd(fd, ' ');
	}
}

int		builtin_echo(int fd, char **arg)
{
	if (arg_len(arg) == 1)
	{
		ft_putchar_fd(fd, '\n');
		return (1);
	}
	if (ft_strcmp(arg[1], "-n") == 0)
		echo_print(arg, 2, fd);
	else
	{
		echo_print(arg, 1, fd);
		ft_putchar_fd(fd, '\n');
	}
	return(0);
}