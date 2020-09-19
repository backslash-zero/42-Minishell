/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_cleanup_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 11:22:58 by celestin          #+#    #+#             */
/*   Updated: 2020/09/19 11:32:03 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		bs_count_conditions(int bs_count, t_parsing_tool *tool, int i)
{
	if (tool->open && tool->quote == '\'')
		return (0);
 	if (!tool->open && tool->input[i] == '\"' && bs_count % 2 == 0 && bs_count != 0)
	{
		if (i > tool->size)
		{
			if (ft_strrchr(&tool->input[i], '\"'))
				return (0);
			return (1);
		}
		else
			return (1);
	}
	if (bs_count % 2 != 0)
	{
		if (is_space(tool->input[i]) && !tool->open)
			return (1);
		if (!tool->input[i])
			return (1);
	}
	return (0);
}

int		backslash_loop_checker(t_parsing_tool *tool)
{
	int i;
	int bs_count;

	i = 0;
	bs_count = 0;
	while (tool->input[i])
	{
		while (is_backslash(tool->input[i]))
		{
			bs_count++;
			i++;
		}
		if (bs_count_conditions(bs_count, tool, i))
			return (-1);
		if (is_quote(tool->input[i]) && (bs_count % 2 == 0))
			switcher_quote(tool, i);
		bs_count = 0;
		if (!tool->input[i])
			return (0);
		i++;
	}
	return (0);
}
