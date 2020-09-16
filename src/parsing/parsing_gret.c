/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_gret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 12:14:45 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/16 17:54:33 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		insert_ret(t_parsing_tool *tool, int i)
{
	char	*newstr;
	int		j;
	int		k;
	char	*ret;

	k = i;
	j = 0;
	ret = ft_itoa(g_ret);
	if (!(newstr = malloc(sizeof(char) *
		(ft_strlen(ret) + (ft_strlen(tool->input) - 2) + 1))))
		return (0);
	ft_strncpy(newstr, tool->input, i);
	ft_strncpy(&newstr[i], ret, ft_strlen(ret));
	i = i + ft_strlen(ret);
	j = k + 2;
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	assign_and_free(&newstr, &tool->input);
	return (1);
}

int		replace_g_ret(char **arg_list, int i)
{
	int				j;
	t_parsing_tool	tool;

	init_tool(&tool);
	tool.input = ft_strdup(arg_list[i]);
	j = 0;
	while (tool.input[j])
	{
		if (is_quote(tool.input[j]) && !check_bf_bs(tool.input, j))
			switcher_quote(&tool, tool.input[j]);
		if (is_dollar(tool.input[j]) && tool.input[j + 1] == '?'
			&& !(tool.open && tool.quote == '\'') && !check_bf_bs(tool.input, j))
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
	int i;

	i = 0;
	if (ft_strlen(str) < 2)
		return (0);
	while (str[i])
	{
		if (i > 0)
		{
			if ((ft_strnstr(&str[i], "$?", 2) != NULL) && !(ft_strnstr(&str[i - 1], "\\$?", 3) != NULL))
				return (1);
		}
		else
		{
			if (ft_strnstr(str, "$?", 2) != NULL)
				return (1);
		}
		i++;
	}
	return (0);
}
