#include "../../incs/minishell.h"

char	**semicolon(char **arg, int i, int len_new_arg_list)
{
	char **arg_list;
	int j;
	int	n;

	j = 0;
	if (!(arg_list = malloc(sizeof(char *) * (len_new_arg_list + 1))))
		return (NULL);
	n = i - len_new_arg_list;
	// printf("len_new_arg_list: %d\n", len_new_arg_list);
	while (j < len_new_arg_list)
	{
		// printf("j: %d\n", j);
		// printf("n: %d\n", n);
		// printf("arg[n]: %s\n", arg[n]);
		arg_list[j] = ft_strdup(arg[n]);
		j++;
		n++;
	}
	arg_list[j] = NULL;
	return (arg_list);
}