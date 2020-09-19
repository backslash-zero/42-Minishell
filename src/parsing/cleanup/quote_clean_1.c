/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_clean_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:04:09 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/19 11:33:51 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		find_pos_nextquote(int i, t_newstr *output)
{
	int j;

	j = i + 1;
	if (output->quote == '\'')
	{
		while (output->str[j] != output->quote)
			j++;
	}
	else if (output->quote == '\"')
	{
		while (output->str[j] != output->quote || (check_bf_bs(output->str, j)))
			j++;
	}
	return (j);
}

int		find_nextquote(int *i, t_newstr *output)
{
	int		j;
	int		old;
	int		new;
	char	*newstr;
	int		bs_count;

	old = 0;
	new = 0;
	bs_count = bs_count_inquote(output, *i, j);
	j = find_pos_nextquote(*i, output);
	output->len -= 2 + bs_count;
	if (!(newstr = malloc(sizeof(char) * (output->len + 1))))
		return (0);
	while (output->str[old])
	{
		if (old != *i && old != j)
		{
			if (!(is_backslash(output->str[old]) && output->quote == '\"' && old < j))
				newstr[new++] = output->str[old];
			else
				bs_count++;
		}
		old++;
	}
	newstr[new] = '\0';
	output->str = newstr;
	*i = j - bs_count - 1;
	return (1);
}

void	init_newstr(t_newstr *output)
{
	output->expand = 1;
	output->open = 0;
	output->quote = '\0';
}

int		clear_quotes(t_newstr *output)
{
	int i;

	i = 0;
	while (output->str[i])
	{
		if (check_char_quote(output->str, i))
		{
			output->open = 1;
			output->quote = output->str[i];
			if (!find_nextquote(&i, output))
				return (0);
			// tmp et free ici??? 
		}
		else
			i++;
	}
	return (1);
}

char	*clean_substring(char *str)
{
	t_newstr output;

	output.str = str;
	output.len = ft_strlen(str);
	init_newstr(&output);
	if (!clear_quotes(&output))
		return (NULL);
	return (output.str);
}
