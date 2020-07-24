/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:54:38 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/24 18:55:06 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		checkifquotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (is_quote(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int		removequotes(char **arg_list, int i)
{
	char *tmp;

	tmp = arg_list[i];
	if (!(arg_list[i] = clean_substring(tmp)))
		return (0);
	free(tmp);
	return (1);
}

int		cleanup_quotes(char **arg_list)
{
	int i;

	i = 0;
	while (arg_list[i])
	{
		if (checkifquotes(arg_list[i]))
		{
			if (!removequotes(arg_list, i))
			{
				free(arg_list);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
