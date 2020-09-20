/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash_cleanup_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 11:17:22 by celestin          #+#    #+#             */
/*   Updated: 2020/09/19 10:43:19 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		check_backslash(t_parsing_tool *tool)
{
	init_tool(tool);

	if (!backslash_loop_checker(tool))
		return (0);
	return (1);
}

int		new_len_backslash(t_parsing_tool *tool)
{
	int i;
	int count;
	int n;

	i = 0;
	count = 0;
	n = 1;

	while (tool->input[i])
	{
		if (i > 0)
		{
			if (is_backslash(tool->input[i - 1]) && n && !(tool->open))
			{	
				count++;
				if (is_backslash(tool->input[i]))
					n = 0;
			}
			else
				n = 1;
		}
		if (is_quote(tool->input[i]))
			switcher_quote(tool, i);
		i++;
	}
	return (ft_strlen(tool->input) - count);
}

int		ft_clean_backslash(char **arg_list, int a)
{
	t_parsing_tool	tool_newstr;
	t_parsing_tool	tool_oldstr;

	init_tool(&tool_newstr);
	init_tool(&tool_oldstr);
	tool_oldstr.input = arg_list[a];
	if (!(tool_newstr.input = malloc(sizeof(char) * (new_len_backslash(&tool_oldstr) + 1))))
		return (0);
	copynew_bs_str(&tool_newstr, &tool_oldstr);
	assign_and_free(&tool_newstr.input, &arg_list[a]);
	return (1);
}

void	copynew_bs_str(t_parsing_tool *tool_newstr, t_parsing_tool *tool_oldstr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	init_tool(tool_oldstr);
	while (tool_oldstr->input[i])
	{
		if (is_quote(tool_oldstr->input[i]))
			switcher_quote(tool_oldstr, i);
		if (is_backslash(tool_oldstr->input[i]) && !tool_oldstr->open)
		{
			i++;
		}
		if (tool_oldstr->input[i] != '\0')
		{
			tool_newstr->input[j] = tool_oldstr->input[i];
			i++;
			j++;
		}
	}
	tool_newstr->input[j] = '\0';
}

int		ft_backslash(char **arg_list)
{
	int	i;

	i = 0;
	while (arg_list[i])
	{
		if (ft_strrchr(arg_list[i], '\\'))
		{
			if (!ft_clean_backslash(arg_list, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int		check_bf_bs(char *str, int i)
{
	if (i == 0)
		return (0);
	else if (i > 0)
	{
		if (is_backslash(str[i - 1]))
			return (1);
	}
	return (0);
}
