/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 19:05:26 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/09 18:24:33 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	init_tool(t_parsing_tool *tool)
{
	tool->quote = '\0';
	tool->open = 0;
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

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int		is_dollar(char c)
{
	if (c == '$')
		return (1);
	else
		return (0);
}

int		is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int		is_semic(char c)
{
	if (c == ';')
		return (1);
	else
		return (0);
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
