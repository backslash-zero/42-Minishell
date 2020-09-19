/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_clean_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 18:54:38 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/19 11:36:06 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		bs_count_inquote(t_newstr *output, int i, int j)
{
	int count;

	count = 0;
	while (i < j)
	{
		if (check_bf_bs(output->str, i) && is_bs_spec(output->str[i]) && output->quote == '\"' && i < j)
			count++;
		i++;
	}
	return (count);
}

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
