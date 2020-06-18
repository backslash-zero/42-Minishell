#include "../../incs/minishell.h"

char	*ft_addsubstr(int i, int j, t_parsing_tool *tool)
{
	int len;
	char *str;

	if (isquote(tool->input[i]))
	{
		i++;
		j--;
	}
	len = j - i + 1;
	if (!(str = malloc(sizeof(char) * (len))))
		return (NULL);
	len = 0;
	while (i < j)
	{
		str[len] = tool->input[i]; 
		i++;
		len++;
	}
	str[len] = '\0';
	return(str);
}

int		size_arg_tool(t_parsing_tool *tool)
{
	int		count;
	int		i;
	int		n;

	i = 0;
	n = 1;
	count = 0;
	while (tool->input[i])
	{
		if (isquote(tool->input[i]))
			switcher_quote(tool, tool->input[i]);
		if (tool->input[i] != ' ' && n != 0 && !tool->open)
		{
			count++;
			n = 0;
		}
		if (tool->input[i] == ' ' && !tool->open)
			n++;
		i++;
	}
	if (tool->open)
		return (-1);
	return (count);
}

char		**ft_split_args(t_parsing_tool *tool)
{
	char	**arg;
	int		n;
	int		i;
	int		j;

	if (!(arg = malloc(sizeof(char *) * (tool->size + 1))))
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	arg[tool->size] = NULL;
	n = 0;
	i = 0;
	j = 0;
	while (tool->input[i])
	{
		while ((tool->input[j] != ' ' && tool->input[j] != '\0')
				|| (tool->input[j] != ' ' && tool->open))
		{
			if (isquote(tool->input[j]))
				switcher_quote(tool, tool->input[j]);
			j++;
		}
		if (j - i > 0)
		{
			if (!(arg[n++] = ft_addsubstr(i, j, tool)))
			{
 				ft_strerror(NULL, NULL, NULL, NULL);
 				return (NULL);
 			}
			i = j;
		}
		if (j != '\0')
		{
			i++;
			j++;
		}
	}
	return(arg);
}

char	**parsing(char *input)
{
	t_parsing_tool	tool;

	init_tool(&tool);
	if (!(tool.input = ft_clean_input(input, &tool)))
		return (NULL);
	init_tool(&tool);
	if ((tool.size = size_arg_tool(&tool)) == -1)
	{
		ft_error(SYNTAX_ERR, NULL, NULL, NULL);
		return (NULL);
	}
	init_tool(&tool);
	if(!(tool.arg = ft_split_args(&tool)))
		return (NULL);
	free(tool.input);
	return (tool.arg);
}
