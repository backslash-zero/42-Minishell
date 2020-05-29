#include "../../incs/minishell.h"

int 	builtin_cd(char **arg)
{
     printf("im in cd\n");
    return(update_pwd());
}
