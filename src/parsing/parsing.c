/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:24:14 by cmeunier          #+#    #+#             */
/*   Updated: 2020/08/12 11:58:24 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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
		quote_checker(tool, i, &n);
		if (semic_checker(tool, i, &n) || redir_pipe_checker(tool, &i, &n))
			return (-1);
		if (tool->input[i] != ' ' && n != 0)
		{
			count++;
			n--;
		}
		if (is_space(tool->input[i]) && !tool->open)
			n = 1;
		i++;
	}
	if (tool->open)
		return (-1);
	return (count);
}

void	skipspaces(t_parsing_tool *tool, int *i, int *j)
{
	while (is_space(tool->input[*i]))
	{
		*i += 1;
		*j += 1;
	}
}

int		ft_split_args(t_parsing_tool *tool)
{
	int		n;
	int		i;
	int		j;

	n = 0;
	i = 0;
	j = 0;
	skipspaces(tool, &i, &j);
	while (tool->input[i] && n < tool->size)
	{
		while ((!is_space(tool->input[j]) && !is_semic(tool->input[j])
				&& !is_redir_or_pipe(tool->input[j])
				&& tool->input[j] != '\0') || (tool->open))
		{
			if (is_quote(tool->input[j]))
				switcher_quote(tool, tool->input[j]);
			j++;
		}
		if (!append_string_to_arg(&i, &j, &n, tool))
			return (0);
		if (!append_semicolon(&i, &j, &n, tool))
			return (0);
		if (!append_redir_pipe(&i, &j, &n, tool))
			return (0);
		if (j++ != '\0')
			i++;
	}
	return (1);
}

char	**malloc_arg(t_parsing_tool *tool)
{
	char **arg;

	if (!(arg = malloc(sizeof(char *) * (tool->size + 1))))
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	arg[tool->size] = NULL;
	return (arg);
}

char	**parsing(char *input)
{
	t_parsing_tool	tool;

	tool.input = ft_strdup(input);
	init_tool(&tool);
	tool.empty_var = 0;
	if (expand_env(&tool) == -1)
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	init_tool(&tool);
	if ((tool.size = size_arg_tool(&tool)) == -1)
	{
		ft_error(SYNTAX_ERR, NULL, NULL, NULL);
		return (NULL);
	}
	if (!(tool.arg = malloc_arg(&tool)))
		return (NULL);
	init_tool(&tool);
	if (!(ft_split_args(&tool)))
		return (NULL);
	free(tool.input);
	return (tool.arg);
}
