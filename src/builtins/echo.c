#include "../../incs/minishell.h"

int		builtin_echo(int fd, char **arg)
{
	int		i;
	char	*s2;
	
	if (arg_len(arg) == 1)
	{
		ft_putchar_fd(fd, '\n');
		return (1);
	}
	if (ft_strcmp(arg[1], "-n") == 0)
	{
		i = 2;
		while (arg[i])
		{
			s2 = ft_strtrim_char(arg[i],'"');
			ft_putstr_fd(fd, s2);
			ft_putchar_fd(fd, ' ');
			i++;
		}
	}
	else
	{
		i = 1;
		while (arg[i])
		{
			s2 = ft_strtrim_char(arg[i],'"');
			ft_putstr_fd(fd, s2);
			ft_putchar_fd(fd, ' ');
			i++;
		}
		ft_putchar_fd(fd, '\n');
	}
	free(s2);
	return(0);
}