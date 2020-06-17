#include "../../incs/minishell.h"

char	*ft_addsubstr(char const *s_copy, char *ptr, t_parsing_tool *tool)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	if (ptr - s_copy == 1 && tool->quote)
		return (NULL);
	if (tool->quote)
		len = ptr - s_copy + 1 - 2;
	else
		len = ptr - s_copy + 1;
	if (!(str = malloc(sizeof(char) * (len))))
		return (NULL);
	if (tool->quote)
	{
		ptr--;
		s_copy++;
	}
	while (s_copy < ptr)
	{
		str[i] = *s_copy;
		i++;
		s_copy++;
	}
	str[i] = '\0';
	tool->quote = '\0';
	return (str);
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
		if (tool->input[i] == '\'' || tool->input[i] == '\"')
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

void	switcher_quote(t_parsing_tool *tool, char c)
{
	if (!tool->open)
	{
		tool->open = 1;
		tool->quote = c;
	}
	else if (tool->open == 1 && c == tool->quote)
	{
		tool->open = 0;
		tool->quote = '\0';
	}
}

char		**ft_split_args(t_parsing_tool *tool)
{
	char	**arg;
	char	*ptr;
	char	*s_copy;
	int		n;

	n = 0;
	if (!tool->input || !(arg = malloc(sizeof(char *) * (tool->size + 1))))
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	arg[tool->size] = NULL;
	s_copy = tool->input;
	ptr = s_copy;
	while (*s_copy && n <= tool->size)
	{
		while (*ptr != ' ' && *ptr != '\0')
		{
			if (*ptr == '\'' || *ptr == '\"')
				switcher_quote(tool, *ptr);
			ptr++;
		}
		if (ptr - s_copy > 0 && !tool->open)
		{
			if (!(arg[n++] = ft_addsubstr(s_copy, ptr, tool)))
			{
 				ft_strerror(NULL, arg, NULL, NULL);
 				return (NULL);
 			}
			s_copy = ptr;
		}
		if (*ptr++ != '\0' && !tool->open)
			s_copy++;
	}
	return (arg);
}

int		test_empty_quote(char c, char d)
{
	if (c == d)
	{
		if (c == '\"' || c == '\'')
			return (1);
	}
	return (0);
}

int		test_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int		new_input_len(char *str, t_parsing_tool *tool)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (test_empty_quote(str[i], str[i + 1]) && !tool->open)
			i+=2;
		else
		{
			if ((!test_empty_quote(str[i], str[i + 1]) && test_quote(str[i]))
				|| (tool->open && str[i] == tool->quote))
				switcher_quote(tool, str[i]);
			i++;
			len++;
		}
	}
	if (tool->open)
		return (-1);
	return (len);
}

void 	ft_copy_new_input(char *str, char *output, t_parsing_tool *tool)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (test_empty_quote(str[i], str[i + 1]) && !tool->open)
			i+=2;
		else
		{
			if ((!test_empty_quote(str[i], str[i + 1]) && test_quote(str[i]))
				|| (tool->open && str[i] == tool->quote))
				switcher_quote(tool, str[i]);
			output[k] = str[i];
			k++;
			i++;
		}
	}
}

char	*ft_clean_input(char *str, t_parsing_tool *tool)
{
	char *output;
	int len;

	if ((len = new_input_len(str, tool)) == -1)
	{
		ft_error(SYNTAX_ERR, NULL, NULL, NULL);
		return (NULL);
	}
	if (!(output = malloc(sizeof(char) * len + 1)))
	{
		ft_strerror(NULL, NULL, NULL, NULL);	
		return (NULL);
	}
	output[len] = '\0';
	ft_copy_new_input(str, output, tool);
	return(output);
}

void	init_tool(t_parsing_tool *tool)
{
	tool->quote = '\0';
	tool->open = 0;
}

char	**parsing(char *input)
{
	t_parsing_tool	tool;
	char			**arg;

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
	if(!(arg = ft_split_args(&tool)))
		return (NULL);
	free(tool.input);
	return (arg);
}
