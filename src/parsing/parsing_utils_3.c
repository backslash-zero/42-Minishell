/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:08:29 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/24 18:44:13 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int		is_equal(char c)
{
	if (c == '=')
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

int		test_lone_dollar(char *str, int i)
{
	if (str[i + 1] == '\0'
		|| is_dollar(str[i + 1])
		|| is_space(str[i + 1])
		|| is_semic(str[i + 1])
		|| is_equal(str[i + 1]))
	{
		return (1);
	}
	return (0);
}
