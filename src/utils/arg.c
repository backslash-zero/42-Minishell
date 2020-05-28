#include "minishell.h"

int     arg_len(char **arg)
{
    int i = 0;

    while (arg[i])
        i++;
    return(i);
}