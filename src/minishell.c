#include "minishell.h"

void    ft_print(char *s)
{
    int i;
    int j;

    i = ft_strlen(s);
    j = -1;
    while (++j <= i)
        write(1, &s[j], 1);
}

int main(int ac, char **av)
{
    char    buffer[150];
    char    *s;
    char    *p;
    char    **arg_list;
    int         i;
    pid_t   process;

    while (1)
    {
        ft_print("Minishell >");
        read(1, buffer, 150);
        buffer[ft_strlen(buffer) - 1]= '\0';
        if (ft_strcmp("exit",buffer) == 0)
            exit(0);
        p = ft_strdup(buffer);
        arg_list = ft_split(p, ' ');
        process = fork();
        if (process == 0)
        {
            s = ft_strjoin("/bin/", arg_list[0]);
            if ((execve(s, arg_list, NULL)) == -1)
                ft_print(strerror(errno));
            exit(0);
        }
        else
            wait(&process);
        i = 0;
        while (arg_list[i] != NULL)
        {
            free(arg_list[i]);
            i++;
        }
        free(p);
    }
    return (0);
}