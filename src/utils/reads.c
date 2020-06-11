#include "../../incs/minishell.h"

int		launch(char *input, t_parse *parse)
{
    char    *s;
    char    **arg_list;
	char	**arg;
    pid_t   process;

	/*if (ft_strcmp("exit",input) == 0)
		exit(0);*/
	if(!(arg = ft_split(input, ' ')))
		return (ft_strerror(NULL, NULL, NULL, NULL));
	int i;
	int k;

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
			return (ft_strerror(NULL, NULL, NULL, NULL));
		process = fork();
		if (process == -1)
			return (ft_strerror(NULL, arg_list, NULL, NULL));
		if (process == 0)
		{
			if (ft_checkbuiltins(arg_list, parse) == 0)
			{
				kill(process, SIGCHLD);
				ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]);
			}
			/*s = ft_strjoin("/bin/", arg_list[0]);
			if ((execve(s, arg_list, NULL)) == -1)
				ft_putstr(strerror(errno));*/
		}
		else
			wait(&process);
		i++;
		/*if (arg_list)
			free_tab(arg_list);*/
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
