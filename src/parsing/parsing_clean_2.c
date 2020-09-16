/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:54:38 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/16 16:46:45 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		check_char_quote(char *str, int i)
{
	if (is_quote(str[i]))
	{
			if (i > 0)
			{
				if (!is_backslash(str[i - 1]))
					return (1);
			}
			else
				return (1);
	}
	return (0);
}

int		checkifquotes(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_char_quote(str, i))
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
		// printf("i:%d\n");
		if (checkifquotes(arg_list[i]))
		{
			// printf("i:%d arglist[i]: %c\n",i, arg_list[i]);
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
