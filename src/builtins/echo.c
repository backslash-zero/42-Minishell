#include "../../incs/minishell.h"

int		builtin_echo(char **s)
{
	char	*s2;

	if (ft_strcmp(s[1], "-n") == 0)
	{
		s2 = ft_strtrim_char(s[2],'"');
		ft_putstr(s2);
	}
	else
	{
		s2 = ft_strtrim_char(s[1],'"');
		ft_putstr(s2);
		ft_putchar('\n');
	}
	free(s2);
	return(0);
}