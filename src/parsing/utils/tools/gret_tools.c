/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gret_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:12:07 by celestin          #+#    #+#             */
/*   Updated: 2020/09/25 00:49:46 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

void		insert_copy_rest(t_parsing_tool *tool, char *newstr, int i, int j)
{
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
}

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
	{
		free(ret);
		return (0);
	}
	ft_strncpy(newstr, tool->input, i);
	ft_strncpy(&newstr[i], ret, ft_strlen(ret));
	i = i + ft_strlen(ret);
	j = k + 2;
	insert_copy_rest(tool, newstr, i, j);
	free(ret);
	assign_and_free(&newstr, &tool->input);
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
			if ((ft_strnstr(&str[i], "$?", 2) != NULL)
				&& !(ft_strnstr(&str[i - 1], "\\$?", 3) != NULL))
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
