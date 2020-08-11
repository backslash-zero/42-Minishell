#include "../../incs/minishell.h"

static void	printtab(char **tab)
{
	int i = 0;
	printf("len tab: %d\n", arg_len(tab));
	while (tab[i])
	{
		printf("str-%d: %s\n", i, tab[i]);
		i++;
	}
}

char	**tablst(t_list *lst)
{
	char	**ret;
	t_list	*tmp;
	int		i;

	ret = NULL;
	tmp = NULL;
	if (!(ret = malloc((ft_lstsize(lst) + 1) * sizeof(*ret))))
		return (NULL);
	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (!(ret[i] = ft_strdup(tmp->content)))
			return (NULL);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	fd_dup(int i)
{
	static int input;
	static int output;

	if (i == 0)
	{
		input = dup(0);
		output = dup(1);
	}
	else if (i == 1)
	{
		dup2(input, 0);
		dup2(output, 1);
	}
}

int		launch_exec(char **arg, t_parse *parse, char **arg_list)
{
	int	ret_red;
	int	ret_exec;
	
	fd_dup(0);
	ret_red = redirection(arg_list, parse);
	if (!ret_red)
	{
		if (!ft_checkbuiltins(arg_list, parse, 1))
		{
			ret_exec = ft_exec(arg_list);
			if (ret_exec == -1)  //error with fork
				return (ft_strerror(NULL, NULL, "fork", NULL));
			else if (ret_exec == -2)
				return (ft_error(CMD_NOT_FOUND, NULL, NULL, arg_list[0]));
		}
		return (1);
	}
	fd_dup(1);
	// else if (ret_red == -1) already done inside of redirection func
	return (0);
}

int		ft_exec(char **arg_list)
{
	pid_t		proc;
	int		status;
	char	*s;
	char	**tab_env;

	if (!(tab_env = tablst(g_env)))
		return (-1);
	if ((proc = fork()) == -1)
	{
		free_tab(tab_env);
		return (-1);
	}
	if (proc == 0)
	{
		s = find_path_env(tab_env, arg_list[0]);
		if ((execve(s, arg_list, tab_env)) == -1)
		{
			free(s);
			free_tab(tab_env);
			return (-2);
		}
		//free(s);
	}
	else if (proc > 0)
	{
		if (wait(&status) == -1)
		{
			free_tab(tab_env);
			return (-1);
		}
	}
	free_tab(tab_env);
	return (0);
}

int		launch(char *input, t_parse *parse)
{
    char    **arg_list;
	char	**arg;
	int 	i;
	int 	len_new_arg_list;

	if(!(arg = parsing(input)))
		return (0);
	i = 0;
	while (arg[i] != NULL)
	{
		len_new_arg_list = 0;
		while (i < arg_len(arg) && ft_strcmp(arg[i], ";") != 0)
		{
			len_new_arg_list++;
			i++;
		}
		if ((arg_list = semicolon(arg, i, len_new_arg_list)) == NULL)
		{
			free_tab(arg_list);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		if (!cleanup_quotes(arg_list))
		{
			free_tab(arg_list);
			return (ft_strerror(NULL, arg, NULL, NULL));
		}
		// printtab(arg_list);
		launch_exec(arg, parse, arg_list);
		if (arg[i] == NULL)
		{
			free_tab(arg_list);
			break ;
		}	
		free_tab(arg_list);
		i++;
	}
	// free_tab(arg_list);
	free_tab(arg);
	// free_tab(arg);
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
