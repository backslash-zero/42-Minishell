#include "../../incs/minishell.h"

int         ft_strerror(void *tofree, char **tab, char *param, char *param2)
{
	if (!param && !param2)
		ft_printf_fd(2, "Minishell: %s\n", strerror(errno));
	else if (param && !param2)
		ft_printf_fd(2, "Minishell: %s: %s\n", param, strerror(errno));
	else
		ft_printf_fd(2, "Minishell: %s: %s: %s\n", param, param2, strerror(errno));
	if (tofree)
		free(tofree);
	if (tab)
		free_tab(tab);
	return (-1);
}

int        ft_error(char *msg, char *tofree, char **tab, char *param)
{
	int i;

	i = 0;
	if(param)
		ft_printf_fd(2, msg, param);
	else
		ft_printf_fd(2, msg);
	if (tofree)
		free(tofree);
	if (tab)
		free_tab(tab);
	return (-1);
}