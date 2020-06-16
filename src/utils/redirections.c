#include "../../incs/minishell.h"

int     r_anglebracket(char **arg, t_parse *parse)
{
        int i;
        int fd;

        fd = 1;
        while (arg[i] && (ft_strcmp(arg[i], ">")) != 0)
            i++;
        if (arg[i] && (ft_strcmp(arg[i], ">") == 0))
        {
            i++;
            if ((fd = open(arg[i], O_CREAT | O_WRONLY | O_TRUNC)) == -1)
                ft_strerror(NULL, arg, NULL, NULL);
            ft_checkbuiltins(arg, parse, fd);
        }
        return (1);
}

int     r_dbanglebracket(char **arg, t_parse *parse)
{
        int i;

        while (arg[i] && (ft_strcmp(arg[i], ">>")) != 0)
            i++;
        if (arg[i] && (ft_strcmp(arg[i], ">>")) == 0)
            printf("Bracket found\n");
        return (1);
}

int     redirection(char **arg, t_parse *parse)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (ft_strcmp(arg[i], ">") == 0)
            r_anglebracket(arg, parse);
        else if (ft_strcmp(arg[i], ">>") == 0)
            r_dbanglebracket(arg, parse);
        i++;
    }
    return (0);
}