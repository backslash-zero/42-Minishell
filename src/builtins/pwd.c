#include "../../incs/minishell.h"

// We need to set all env variable in chained list at the beginning

char	*current_dir(void)
{
	char *dir;

	dir = NULL;
	if(!(dir = getcwd(dir, 0)))
		ft_error();
	return(dir);
}

int		builtin_pwd(void)
{
	ft_putstr(current_dir());
	return(0);
}
