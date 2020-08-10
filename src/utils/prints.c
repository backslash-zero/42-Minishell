#include "../../incs/minishell.h"

void    print_prompt_prefix(void)
{
    write(1, "\033[1;35m", 7);
    write(1, "minishell", 9);
    write(1, "\033[1;33m", 7);
    write(1, " > ", 3);
    write(1, "\033[0m", 4);
}
