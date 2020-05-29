#include "../../incs/minishell.h"

int     arg_len(char **arg)
{
    int i;

    i = 0;
	if (arg)
		while (arg[i])
			i++;
	return (i);
}
