#include "../../incs/minishell.h"

char    **deletebracket(char **arg)
{
    int i;
    int j;
    char **s;

    i = 0;
    j = 0;
    while (arg[i]  != NULL && (ft_strcmp(arg[i], ">")) != 0 && (ft_strcmp(arg[i], ">>")) != 0)
    {
        if ((ft_strcmp(arg[i], "<")) != 0)
            j++;
        i++;
    }
    if (!(s = (char **)malloc(sizeof(char *) * (j + 1))))
        return (NULL);
    i = 0;
    j = 0;
    while (arg[i] != NULL && (ft_strcmp(arg[i], ">")) != 0 && (ft_strcmp(arg[i], ">>")) != 0)
    {
        if ((ft_strcmp(arg[i], "<")) != 0)
        {
            if ((s[j] = ft_strdup(arg[i])) == NULL)
            {
                free_tab (s);
                return (NULL);
            }
            j++;
        }
        i++;     
    }
    s[j] = NULL;
    return (s);
}

int permission_check(int fd)
{
    struct stat buff;

    if ((fstat(fd, &buff) == -1))
        return (-1);
    printf("S_IFMT	 = %d\n", S_IFMT);
    printf("S_IFSOCK = %d\n", S_IFSOCK);
    printf("S_IFLNK = %d\n", S_IFLNK);
    printf("S_IFREG	 = %d\n", S_IFREG);
    printf("S_IFBLK	 = %d\n", S_IFBLK);
    printf("S_IFDIR  = %d\n", S_IFDIR);
    printf("S_IFCHR	 = %d\n", S_IFCHR);
    printf("S_IFIFO  = %d\n", S_IFIFO);
    printf("S_ISUID	 = %d\n", S_ISUID);
    printf("S_ISGID	 = %d\n", S_ISGID);
    printf("S_ISVTX	 = %d\n", S_ISVTX);

    printf("\nS_IRWXU	 = %d\n", S_IRWXU);
    printf("S_IRUSR = %d\n", S_IRUSR);
    printf("S_IWUSR = %d\n", S_IWUSR);
    printf("S_IXUSR = %d\n", S_IXUSR);
    
    printf("\nS_IRWXG = %d\n", S_IRWXG);
    printf("S_IRGRP = %d\n", S_IRGRP);
    printf("S_IWGRP = %d\n", S_IWGRP);
    printf("S_IXGRP = %d\n", S_IXGRP);

    printf("\nS_IRWXO= %d\n", S_IRWXO);
    printf("S_IROTH = %d\n", S_IROTH);
    printf("S_IWOTH = %d\n", S_IWOTH);
    printf("S_IXOTH = %d\n", S_IXOTH);

    printf("\nst_mode = %d\n", buff.st_mode);
    if (buff.st_mode >= 32896)
        return (1);
    return (0);
}


int     r_anglebracket(char **arg, t_parse *parse)
{
    int i;
    int fd;
    int ret_exec;
    char **arg_list;

    fd = 1;
    i = 0;
    while (arg[i] && (ft_strcmp(arg[i], ">")) != 0)
        i++;
    if (arg[i] && (ft_strcmp(arg[i], ">") == 0))
    {
        i++;
        ft_putstr_fd(3, "mode00\n");
        if ((fd = open(arg[i], O_CREAT | O_WRONLY | O_TRUNC, 0644)) == -1)
        {
            ft_strerror(NULL, arg, NULL, NULL);
            return (-1);
        }
        dup2 (fd, 1);
        if (!(arg_list = deletebracket(arg)))
        {
            close (fd);
            free_tab (arg_list);
            ft_strerror (NULL, arg, NULL, NULL);
            return (-1);
        }
        if (permission_check(fd) != 0)
        {
            if (!ft_checkbuiltins(arg_list, parse))
            {
                ret_exec = ft_exec(arg_list);
                if (ret_exec == -1)
                    ft_strerror(NULL, NULL, "fork", NULL);
                else if (ret_exec == -2)
                {
                    ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
                    close (fd);
                    exit(127);
                }
            }
        }
        else
        {
            close (fd);
            ft_strerror(NULL, NULL, "bad file", NULL);
            return (1);
        }
    }
    close (fd);
    //free (arg_list);
    return (1);
}

int     r_dbanglebracket(char **arg, t_parse *parse)
{
    int i;
    int fd;
    int ret_exec;
    char **arg_list;

    i = 0;
    fd = 1;
    while (arg[i] && (ft_strcmp(arg[i], ">>")) != 0)
        i++;
    if (arg[i] && (ft_strcmp(arg[i], ">>") == 0))
    {
        i++;
        if ((fd = open(arg[i], O_CREAT | O_WRONLY | O_APPEND, 0644)) == -1)
        {
            ft_strerror(NULL, arg, NULL, NULL);
            return (-1);
        }
        dup2 (fd, 1);
        if ((arg_list = deletebracket(arg)) == NULL)
        {
            close (fd);
            free_tab (arg_list);
            ft_strerror (NULL, arg, NULL, NULL);
            return (-1);
        }
        if (permission_check(fd) != 0)
        {
            if (!ft_checkbuiltins(arg_list, parse))
            {
                ret_exec = ft_exec(arg_list);
                if (ret_exec == -1)
                    ft_strerror(NULL, NULL, "fork", NULL);
                else if (ret_exec == -2)
                {
                    ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
                    close (fd);
                    exit(127);
                }
            }
        }
        else
        {
            close (fd);
            ft_strerror(NULL, NULL, "bad file", NULL);
            return (1);
        }
    }
    close (fd);
    free (arg_list);
    return (1);
}

int     l_anglebracket(char **arg, t_parse *parse)
{
    int i;
    int fd;
    int ret_exec;
    char **arg_list;

    i = 0;
    while (arg[i] && (ft_strcmp(arg[i], "<")) != 0)
        i++;
    i++;
    if ((fd = open(arg[i], O_RDONLY)) == -1)
    {
        ft_strerror(NULL, arg, NULL, NULL);
        return (-1);
    }
    dup2(fd, 0);
    if ((arg_list = deletebracket(arg)) == NULL)
    {
        close (fd);
        free_tab(arg_list);
        ft_strerror (NULL, arg, NULL, NULL);
        return (-1);
    }
    if (permission_check(fd) != 0)
    {
        if (!ft_checkbuiltins(arg_list, parse))
        {
            ret_exec = ft_exec(arg_list);
            if (ret_exec == -1)
                ft_strerror(NULL, NULL, "fork", NULL);
            else if (ret_exec == -2)
            {
                ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
                close (fd);
                exit(127);
            }
        }
    }
    else
    {
        close (fd);
        ft_strerror(NULL, NULL, "bad file", NULL);
        return (1);
    }
    close (fd);
    //free (arg_list);
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
        else if (ft_strcmp(arg[i], "<") == 0)
            return (l_anglebracket(arg, parse));
        i++;
    }
    return (0);
}


