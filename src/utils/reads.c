#include "../../incs/minishell.h"

void	launch(char *input)
{
    char    *s;
    char    **arg_list;
    pid_t   process;

	if (ft_strcmp("exit",input) == 0)
		exit(0);
	arg_list = ft_split(input, ' ');
	process = fork();
	if (process == -1)
	{
		ft_putstr(strerror(errno));
		exit(0);
	}
	if (process == 0)
	{
		s = ft_strjoin("/bin/", arg_list[0]);
		if ((execve(s, arg_list, NULL)) == -1)
			ft_putstr(strerror(errno));
		
	}
	else
		wait(&process);
	free_tab(arg_list);
}

void	prompt(void)
{
	char	buffer[MAX_INPUT_SIZE];
	int		ret;
	
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
		launch(buffer);
	}
}
