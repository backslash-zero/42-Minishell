#include "../../incs/minishell.h"

int		builtin_exit(char **arg)
{
	int 			i;
	unsigned int	j;
	int 			arg_l;

	ft_putstr("exit\n");
	if ((arg_l = arg_len(arg)) == 1)
		exit(0);
	if (arg_l > 2)
		return (ft_error(MANY_ARGS, NULL, NULL, arg[1]));
	while (arg[1][i])
	{
		if(!(ft_isdigit(arg[1][i])))
		{
			ft_error(EXIT_NUM, NULL, NULL, arg[1]);
			exit(255);
		}
		i++;
	}
	if ((i = ft_atoi(arg[1])) < 0)
		j = (unsigned int)i;
	else
		j = i;
	exit(j);
}
