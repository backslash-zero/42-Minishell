/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:04:09 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/23 19:19:55 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

static int		checkifquotes(char *str)
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

static int		removequotes(char **arg_list, int i)
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
				free (arg_list);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int		find_nextquote(int *i, t_newstr *output)
{
	int j;
	int old;
	int new;
	char *newstr;

	j = *i + 1;
	old = 0;
	new = 0;
	while (output->str[j] != output->quote)
		j++;
	output->len -= 2;
	if (!(newstr = malloc(sizeof(char) * (output->len + 1))))
		return (0);
	while (output->str[old])
	{
		if (old != *i && old != j)
		{
			newstr[new] = output->str[old];
			new++;
		}
		old++;
	}
	newstr[new] = '\0';
	output->str = newstr;
	*i = j - 1; 
	return (1);
}


void	init_newstr(t_newstr *output, char *str)
{
	output->expand = 1;
	output->open = 0;
	output->quote = '\0';
}


int		clear_quotes(t_newstr *output)
{
	int i;
	
	i = 0;
	while(output->str[i])
	{
		if (is_quote(output->str[i]))
		{
			output->open = 1;
			output->quote = output->str[i];
			if(!find_nextquote(&i, output))
				return (0);
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
	init_newstr(&output, str);
	if (!clear_quotes(&output))
		return (NULL);
	return(output.str);
}
