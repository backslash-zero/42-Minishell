#include "../../incs/minishell.h"

void    ft_print(char *s)
{
    int i;
    int j;

    i = ft_strlen(s);
    j = -1;
    while (++j <= i)
        write(1, &s[j], 1);
}

void    ft_putstr(char *s)
{
    write(1, s, ft_strlen(s));
}

void    print_prompt_prefix(void)
{
    write(1, "\033[1;35m", 7);
    write(1, "MiniShell", 9);
    write(1, "\033[1;33m", 7);
    write(1, " > ", 3);
    write(1, "\033[0m", 4);
}
