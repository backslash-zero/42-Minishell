/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bs_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:17:21 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 21:24:56 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

void	ft_clean_and_cpy_switchers(t_parsing_tool *tool, int i)
{
	if (is_backslash(tool->input[i]))
	{
		switcher_bs(tool, i);
		if (tool->pre_bs)
			tool->expand = 0;
	}
	if (is_quote(tool->input[i]) && !tool->pre_bs)
	{
		if (switcher_quote(tool, i))
			tool->expand = 0;
	}
	cancel_pre_bs(tool, i);
}

void	ft_clean_and_cpy(t_parsing_tool *tool)
{
	int i;
	int j;

	i = 0;
	j = 0;
	tool->expand = 1;
	while (tool->input[i])
	{
		ft_clean_and_cpy_switchers(tool, i);
		if (tool->expand)
		{
			tool->new_str[j] = tool->input[i];
			j++;
		}
		tool->expand = 1;
		i++;
	}
	tool->new_str[j] = '\0';
}

void	len_cleaned_str(t_parsing_tool *tool)
{
	int i;
	int n;

	i = 0;
	n = 1;
	tool->new_size = tool->size;
	while (tool->input[i])
	{
		if (conditions_xtra_bs(tool, i))
			tool->new_size--;
		bs_checker(tool, i);
		if (is_quote(tool->input[i]) && !tool->pre_bs)
		{
			if (switcher_quote(tool, i))
				tool->new_size--;
		}
		cancel_pre_bs(tool, i);
		i++;
	}
}

int		process_str(char **arg_list, int i)
{
	int				new_len;
	t_parsing_tool	tool;

	init_tool(&tool);
	tool.input = arg_list[i];
	tool.size = ft_strlen(arg_list[i]);
	len_cleaned_str(&tool);
	if (!(tool.new_str = malloc(sizeof(char) * (tool.new_size + 1))))
		return (0);
	init_tool(&tool);
	ft_clean_and_cpy(&tool);
	assign_and_free(&tool.new_str, &arg_list[i]);
	return (1);
}

int		ft_clean_bs_quote(char **arg_list)
{
	int i;

	i = 0;
	while (arg_list[i])
	{
		if (checkifquotes(arg_list[i]) || ft_strrchr(arg_list[i], '\\'))
		{
			if (!process_str(arg_list, i))
			{
				free(arg_list);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
