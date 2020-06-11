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
}