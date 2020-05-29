#include "../../incs/minishell.h"

void    ft_putstr(char *s)
{
    write(1, s, ft_strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void    print_prompt_prefix(void)
{
    write(1, "\033[1;35m", 7);
    write(1, "MiniShell", 9);
    write(1, "\033[1;33m", 7);
    write(1, " > ", 3);
    write(1, "\033[0m", 4);
}
