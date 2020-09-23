/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_tools_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:37:19 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 21:13:14 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

void	switcher_bs(t_parsing_tool *tool)
{
	if (tool->pre_bs && !(tool->open && tool->quote == '\''))
		tool->pre_bs = 0;
	else if (!tool->pre_bs && !(tool->open && tool->quote == '\''))
		tool->pre_bs = 1;
}

void	cancel_pre_bs(t_parsing_tool *tool, int i)
{
	if (!is_backslash(tool->input[i]) || (tool->open && tool->quote == '\''))
		tool->pre_bs = 0;
}

void	bs_checker(t_parsing_tool *tool, int i)
{
	if (is_backslash(tool->input[i]))
		switcher_bs(tool);
}

int		check_backslash(t_parsing_tool *tool)
{
	init_tool(tool);
	if (!backslash_loop_checker(tool))
		return (0);
	return (1);
}

int		conditions_xtra_bs(t_parsing_tool *tool, int i)
{
	if (tool->pre_bs
		&& !(tool->open && tool->quote == '\'')
		&& !(tool->open && tool->quote == '\"'
		&& !is_bs_spec(tool->input[i])))
		return (1);
	return (0);
}
