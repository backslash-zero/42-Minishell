/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_gret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:10:46 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 20:16:24 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		replace_g_ret(char **arg_list, int i)
{
	int				j;
	t_parsing_tool	tool;

	init_tool(&tool);
	tool.input = ft_strdup(arg_list[i]);
	j = 0;
	while (tool.input[j])
	{
		bs_checker(&tool, j);
		if (is_quote(tool.input[j]))
			switcher_quote(&tool, j);
		if (is_dollar(tool.input[j]) && tool.input[j + 1] == '?'
			&& !(tool.open && tool.quote == '\'') && !tool.pre_bs)
		{
			if (!insert_ret(&tool, j))
			{
				free(tool.input);
				return (0);
			}
		}
		cancel_pre_bs(&tool, j);
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
