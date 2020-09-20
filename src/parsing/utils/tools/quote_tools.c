/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:25:01 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 21:05:07 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		check_char_quote(char *str, int i)
{
	if (is_quote(str[i]))
	{
		if (i > 0)
		{
			if (!is_backslash(str[i - 1]))
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int		checkifquotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_char_quote(str, i))
			return (1);
		i++;
	}
	return (0);
}

void	quote_checker(t_parsing_tool *tool, int i, int *n)
{
	if (is_quote(tool->input[i]))
	{
		switcher_quote(tool, i);
		if (!tool->open)
			*n = 0;
	}
}

int		switcher_quote(t_parsing_tool *tool, int i)
{
	if (!tool->open && !tool->pre_bs)
	{
		tool->open = 1;
		tool->quote = tool->input[i];
		return (1);
	}
	else if (tool->open == 1 && tool->input[i] == tool->quote
			&& !(tool->pre_bs && tool->quote == '\"'))
	{
		tool->open = 0;
		tool->quote = '\0';
		return (1);
	}
	return (0);
}
