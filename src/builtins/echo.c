#include "../../incs/minishell.h"

int		builtin_echo(char **arg)
{
	int		i;
	char	*s2;
	
	if (arg_len(arg) == 1)
	{
		ft_putchar('\n');
		return (1);
	}
	if (ft_strcmp(arg[1], "-n") == 0)
	{
		i = 2;
		while (arg[i])
		{
			s2 = ft_strtrim_char(arg[i],'"');
			ft_putstr(s2);
			ft_putchar(' ');
			i++;
		}
	}
	else
	{
		i = 1;
		while (arg[i])
		{
			s2 = ft_strtrim_char(arg[i],'"');
			ft_putstr(s2);
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
	}
	free(s2);
	return(0);
}