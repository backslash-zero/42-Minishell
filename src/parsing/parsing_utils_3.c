/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:08:29 by cmeunier          #+#    #+#             */
/*   Updated: 2020/08/27 20:49:28 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		is_redir_or_pipe(char c)
{
	if (is_pipe(c) ||
		is_redir_l(c) ||
		is_redir_r(c))
		return (1);
	else
		return (0);
}

int		is_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int		is_redir_l(char c)
{
	if (c == '<')
		return (1);
	else
		return (0);
}

int		is_redir_r(char c)
{
	if (c == '>')
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
	if (!envvar_authorized_character(str[i + 1], TRUE))
	{
		return (1);
	}
	return (0);
}

int		replace_g_ret(char **arg_list, int i)
{
	int j;
	t_parsing_tool tool;

	init_tool(&tool);
	tool.input = ft_strdup(arg_list[i]);
	j = 0;
	while (arg_list[i][j])
	{
		if (is_quote(arg_list[i][j]))
			switcher_quote(&tool, arg_list[i][j]);
		if (is_dollar(arg_list[i][j]) && arg_list[i][j + 1] == '?'
			&& !(tool.open && tool.quote == '\''))
		{
			if (!insert_ret(&tool, j))
			{
				free(tool.input);
				return (0);
			}
		}
		j++;
	}
	assign_and_free(&tool.input, &arg_list[i]);
	return (1);
}

int		check_g_ret_var(char **arg_list)
{
	int i;

	i = 0;
	while (arg_list[i])
	{
		if (is_g_ret_var(arg_list[i]))
		{
			if (!(replace_g_ret(arg_list, i)))
				return (0);
		}
		i++;
	}
	return (1);
}

int		is_g_ret_var(char *str)
{
	if (ft_strnstr(str, "$?", ft_strlen(str)) != NULL)
		return (1);
	return (0);
}
