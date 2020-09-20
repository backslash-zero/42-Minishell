/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 17:24:14 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/20 13:40:04 by celestin         ###   ########.fr       */
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
		bs_checker(tool, i);
		quote_checker(tool, i, &n);
		if (semic_checker(tool, i, &n) || redir_pipe_checker(tool, &i, &n))
			return (-1);
		if (!ft_is_space(tool->input[i]) && n != 0)
		{
			count++;
			n--;
		}
		if (ft_is_space(tool->input[i]) && !tool->open)
			n = 1;
		cancel_pre_bs(tool, i);
		i++;
	}
	return (tool->open ? -1 : count);
}

int		conditions_split(t_parsing_tool *tool, int j)
{
	if ((!ft_is_space(tool->input[j])
		&& !(is_semic(tool->input[j]) && !tool->pre_bs)
		&& !(is_redir_or_pipe(tool->input[j]) && !tool->pre_bs)
		&& (tool->input[j] != '\0'))
		|| (tool->open))
		return (1);
	return (0);
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
		while (conditions_split(tool, j))
		{
			bs_checker(tool, j);
			if (is_quote(tool->input[j]))
				switcher_quote(tool, j);
			cancel_pre_bs(tool, j);
			j++;
		}
		if (!parsing_checks(&i, &j, &n, tool))
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
	if (((tool.size = size_arg_tool(&tool)) == -1) || (check_backslash(&tool)))
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
