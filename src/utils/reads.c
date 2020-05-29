#include "../../incs/minishell.h"

void	ft_builtinstab(t_parse *parse)
{
	parse->builtnb[0] = "echo";
	parse->builtnb[1] = "cd";
	parse->builtnb[2] = "pwd";
	parse->builtnb[3] = "export";
	parse->builtnb[4] = "unset";
	parse->builtnb[5] = "env";
	parse->builtnb[6] = "exit";
}

int		ft_echo(char **s)
{
	char	*s2;

	if (ft_strcmp(s[1], "-n") == 0)
	{
		s2 = ft_strtrim_char(s[2],'"');
		ft_putstr(s2);
	}
	else
	{
		s2 = ft_strtrim_char(s[1],'"');
		ft_putstr(s2);
		ft_putchar('\n');
	}
	free(s2);
	return(0);
}

int		ft_cd(char **s)
{
	printf("i'm in cd\n");
	return(0);
}

int		ft_pwd(char **s)
{
	printf("i'm in pwd\n");
	return(0);
}

int		ft_export(char **s)
{
	printf("i'm in export\n");
	return(0);
}

int		ft_unset(char **s)
{
	printf("i'm in unset\n");
	return(0);
}

int		ft_env(char **s)
{
	printf("i'm in env\n");
	return(0);
}

int		ft_exit(char **s)
{
	//free_tab(s);
	//printf("i'm in exit\n");
	//exit(0);

	return(-1);
}

builtfunc_addr	builtins_func[] = {
	&ft_echo, &ft_cd, &ft_pwd, &ft_export, &ft_unset, &ft_env, &ft_exit
};

int		ft_checkbuiltins(char **s, t_parse *parse)
{
	int i;
	int	good;

	i = 0;
	good = 0;
	while (i <= NB_BUILINS && good != 1)
	{
		if (ft_strcmp(s[0], parse->builtnb[i]) == 0)
			good = 1;
		if (good != 1)
			i++;
	}
	if (good == 1)
	{
		if (builtins_func[i](s) == -1)
			return(0);
		return(1);
	}
	else
		return (0);
	/*A amelioer en faisant un exit avec un message d'erreur*/
}




void	launch(char *input, t_parse *parse)
{
    char    *s;
    char    *p;
    char    **arg_list;
    pid_t   process;

	/*if (ft_strcmp("exit",input) == 0)
		exit(0);*/
	arg_list = ft_split(input, ' ');
	process = fork();
	if (process == -1)
	{
		ft_putstr(strerror(errno));
		exit(0);
	}
	if (process == 0)
	{
		if (ft_checkbuiltins(arg_list, parse) == 0)
			kill(process, SIGCHLD);
		/*s = ft_strjoin("/bin/", arg_list[0]);
		if ((execve(s, arg_list, NULL)) == -1)
			ft_putstr(strerror(errno));*/
	}
	else
		wait(&process);
	free_tab(arg_list);
}

void	prompt(void)
{
	char	buffer[MAX_INPUT_SIZE];
	int		ret;
	t_parse	parse;
	int i = 0;

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
		launch(buffer, &parse);
	}
}
