/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 10:53:56 by celestin          #+#    #+#             */
/*   Updated: 2020/09/19 11:34:04 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		clear_quotes_bs(t_newstr *output)
{
	int		i;
	char	*tmp;

	i = 0;
	while (output->str[i])
	{
		if (check_char_quote(output->str, i))
		{
			output->open = 1;
			output->quote = output->str[i];
			if (!find_nextquote(&i, output))
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int		conditions_xtra_bs(t_parsing_tool *tool, int i)
{
	if (tool->pre_bs
			&& !(tool->open && tool->quote == '\'') 
			&& !(tool->open && tool->quote == '\"' && !is_bs_spec(tool->input[i])))
		return (1);
	return (0);
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
		if (is_backslash(tool->input[i]))
			switcher_bs(tool, i);
		if (is_quote(tool->input[i]) && !tool->pre_bs)
		{	
			if (switcher_quote(tool, i))
				tool->new_size--;
		}
		if (!is_backslash(tool->input[i]) || (tool->open && tool->quote == '\''))
			tool->pre_bs = 0;
		i++;
	}
}

int		process_str(char **arg_list, int i)
{
	int				new_len;
	t_parsing_tool 	tool;
	
	init_tool(&tool);
	tool.input = arg_list[i];
	tool.size = ft_strlen(arg_list[i]);
	len_cleaned_str(&tool);
	if(!(tool.new_str = malloc(sizeof(char) * (tool.new_size + 1))))
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

void	ft_clean_and_cpy(t_parsing_tool *tool)
{
	int i;
	int j;

	i = 0;
	j = 0;
	tool->expand = 1;
	while (tool->input[i])
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
		if (!is_backslash(tool->input[i]) || (tool->open && tool->quote == '\''))
			tool->pre_bs = 0;
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

int		arg_cleanup(char **arg)
{
	if (!check_var(arg))
		return (0);
	if (!check_g_ret_var(arg))
		return (0);
	if (!ft_clean_bs_quote(arg))
		return (0);
	return (1);
}
