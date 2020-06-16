#include "../../incs/minishell.h"

int		launch(char *input, t_parse *parse)
{
    char    **arg_list;
	char	**arg;
	int 	i;
	int 	k;
	char	**test;

	if(!(arg = ft_split2(input, ' ', ';')))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	i = 0;
	while (arg[i] != NULL)
	{
		k = 0;
		while(i < arg_len(arg) - 1 && ft_strcmp(arg[i], ";") != 0)
		{
			k++;
			i++;
		}
		if ((arg_list = semicolon(arg, i, k)) == NULL)
			return (ft_strerror(NULL, arg, NULL, NULL));
		if (!(redirection(arg, parse)))
		{
			if ((ft_checkbuiltins(arg_list, parse, 1)) == 0)
				ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			/*else
				ADD EXECVE FOR OTHER BUILTINS LIKE 'ls'*/
		}
		i++;
		free (arg_list);
	}
	free_tab(arg);
	return (0);
}

void	prompt(void)
{
	char	buffer[MAX_INPUT_SIZE];
	int		ret;
	t_parse	parse;

	ft_builtinstab(&parse);
	while (1)
	{
		print_prompt_prefix();
		ret = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
		if (ret == -1)
			exit(errno);
		if (ret)
			buffer[ret - 1] = '\0';
		else
			ft_strlcpy(buffer, "exit", 5);
		if (launch(buffer, &parse) == -1)
			return ;
	}
}
