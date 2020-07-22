/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:08:27 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/21 19:09:19 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		calc_len_newstr(char *var, char *input, char *env_name, int i)
{
	int	len_newstr;

	len_newstr = i;
	len_newstr += ft_strlen(var);
	len_newstr += (ft_strlen(input) - i - 1 - ft_strlen(env_name));
	return (len_newstr);
}

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
