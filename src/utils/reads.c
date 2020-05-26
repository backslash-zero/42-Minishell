#include "minishell.h"

void	launch(char *input)
{
    char    *s;
    char    *p;
    char    **arg_list;
    int     i;
    pid_t   process;

	if (ft_strcmp("exit",input) == 0)
		exit(0);
	p = ft_strdup(input);
	arg_list = ft_split(p, ' ');
	process = fork();
	if (process == 0)
	{
		s = ft_strjoin("/bin/", arg_list[0]);
		if ((execve(s, arg_list, NULL)) == -1)
		{
			ft_print(strerror(errno));
			write(1, "\n", 1);
		}
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

void	prompt(void)
{
	char	buffer[MAX_INPUT_SIZE];
	int		ret;
	
	while (1)
	{
		print_prompt_prefix();
		ret = read(STDIN_FILENO, buffer, MAX_INPUT_SIZE);
		// if (ret == -1)
			// exit and error 
			//ft_print(strerror(errno));
			//exit(0);
		if (ret)
		{
			while (buffer[ret - 1] != '\n')
			{
				ft_putstr("\033[2C\b\b  \033[2D");
				ret += read(STDIN_FILENO, &buffer[ret], MAX_INPUT_SIZE);
			}
			buffer[ret - 1] = '\0';
		}
		else
			ft_strlcpy(buffer, "exit", 5);
		launch(buffer);
	}
}
