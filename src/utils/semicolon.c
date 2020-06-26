#include "../../incs/minishell.h"

char	**semicolon(char **arg, int i, int l)
{
	char **arg_list;
	int j;
	int	k;

	j = 0;
	if (arg[i] != NULL && ft_strcmp(arg[i], ";") == 0)
	{
		if (!(arg_list = (char **)malloc(sizeof(char *) * (l + 1))))
			return (NULL);
		k = i - l;
		i++;
		while (arg[k] && ft_strcmp(arg[k], ";") != 0)
		{
			arg_list[j] = ft_strdup(arg[k]);
			j++;
			k++;
			i++;
		}
		arg_list[j] = NULL;
		return (arg_list);
	}
	else
	{
		/*if (!(arg_list = (char **)malloc(sizeof(char *) * (l + 1))))
			return (NULL);*/
		k = i - l;
		i++;
		printf("arg_list[0] = %s\n", arg_list[0]);
		while (arg[k] && ft_strcmp(arg[k], ";") != 0)
		{
			arg_list[j] = arg[k];
			j++;
			k++;
			i++;
		}
		arg_list[j] = NULL;
		/*printf("l + 1 = %d j = %d\n", l + 1, j);
		int d = 0;
		while (d <= j)
		{
			printf("arg_list[%d] = %s\n", d, arg_list[d]);
			d++;
		}*/
		return (arg_list);
	}
}