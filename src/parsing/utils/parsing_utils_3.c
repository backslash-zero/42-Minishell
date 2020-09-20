/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:08:29 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/17 11:57:27 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

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

int		includes_var(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (is_dollar(str[i]) && !is_backslash(str[i - 1]))
				return (1);
		}
		else
		{
			if (is_dollar(str[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
