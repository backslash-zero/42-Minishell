#include "../../incs/minishell.h"

char    **deletebracket(char **arg)
{
    int i;
    char **arg_list;

    i = 0;
    while (arg[i] && (ft_strcmp(arg[i], ">")) != 0 && (ft_strcmp(arg[i], ">>")) != 0)
        i++;
    if (!(arg_list = (char **)malloc(sizeof(char *) * (i + 1))))
        return (NULL);
    i = 0;
    while (arg[i] && (ft_strcmp(arg[i], ">")) != 0 && (ft_strcmp(arg[i], ">>")) != 0)
    {
        if ((arg_list[i] = ft_strdup(arg[i])) == NULL)
        {
            free_tab (arg_list);
            return (NULL);
        }
        i++;
    }
    arg_list[i] = NULL;
    return (arg_list);
}

int     r_anglebracket(char **arg, t_parse *parse)
{
        int i;
        int fd;
        char **arg_list;

        fd = 1;
        i = 0;
        while (arg[i] && (ft_strcmp(arg[i], ">")) != 0)
            i++;
        if (arg[i] && (ft_strcmp(arg[i], ">") == 0))
        {
            i++;
            if ((fd = open(arg[i], O_CREAT | O_WRONLY | O_TRUNC)) == -1)
                ft_strerror(NULL, arg, NULL, NULL);
            if ((arg_list = deletebracket(arg)) == NULL)
            {
                close (fd);
                free_tab (arg_list);
                ft_strerror (NULL, arg, NULL, NULL);
            }
            if ((ft_checkbuiltins(arg_list, parse, fd)) == 0)
				ft_exec(arg_list);
        }
        close (fd);
        free_tab (arg_list);
        return (1);
}

int     r_dbanglebracket(char **arg, t_parse *parse)
{
        int i;
        int fd;
        char **arg_list;

        i = 0;
        fd = 1;
        while (arg[i] && (ft_strcmp(arg[i], ">>")) != 0)
            i++;
        if (arg[i] && (ft_strcmp(arg[i], ">>") == 0))
        {
            i++;
            if ((fd = open(arg[i], O_CREAT | O_WRONLY | O_APPEND)) == -1)
                ft_strerror(NULL, arg, NULL, NULL);
            if ((arg_list = deletebracket(arg)) == NULL)
            {
                free_tab(arg_list);
                close (fd);
                ft_strerror (NULL, arg, NULL, NULL);
            }
            if ((ft_checkbuiltins(arg_list, parse, fd)) == 0)
                ft_exec(arg_list);
        }
        free_tab(arg_list);
        return (1);
}

int     redirection(char **arg, t_parse *parse)
{
    int i;

    i = 1;
    while (arg[i])
    {
        if (ft_strcmp(arg[i], ">") == 0)
            return (r_anglebracket(arg, parse));
        else if (ft_strcmp(arg[i], ">>") == 0)
            return (r_dbanglebracket(arg, parse));
        i++;
    }
    return (0);
}