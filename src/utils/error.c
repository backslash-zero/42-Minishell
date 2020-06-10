#include "../../incs/minishell.h"

int         ft_strerror(void)
{
	ft_printf_fd(2, "Minishell: %s\n", strerror(errno));
	return (-1);
}

int        ft_error(char *msg, char *param)
{
	if(param)
		ft_printf_fd(2, msg, param);
	else
		ft_printf_fd(2, msg);
	return (-1);
}