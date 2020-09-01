/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_gret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 12:14:45 by cmeunier          #+#    #+#             */
/*   Updated: 2020/08/29 12:20:22 by cmeunier         ###   ########.fr       */
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
		if (is_quote(tool.input[j]))
			switcher_quote(&tool, tool.input[j]);
		if (is_dollar(tool.input[j]) && tool.input[j + 1] == '?'
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
