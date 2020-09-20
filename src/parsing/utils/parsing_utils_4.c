/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 12:24:24 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/19 00:22:44 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

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

void	switcher_bs(t_parsing_tool *tool, int i)
{
	if (tool->pre_bs && !(tool->open && tool->quote == '\''))
		tool->pre_bs = 0;
	else if (!tool->pre_bs && !(tool->open && tool->quote == '\''))
		tool->pre_bs = 1;
}

int 	switcher_quote(t_parsing_tool *tool, int i)
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

int		test_lone_dollar(char *str, int i)
{
	if (!envvar_authorized_character(str[i + 1], TRUE))
		return (1);
	return (0);
}
