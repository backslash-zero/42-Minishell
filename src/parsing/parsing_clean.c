/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:04:09 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/20 17:40:29 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		find_nextquote(int *i, t_newstr *output)
{
	int j;
	int old;
	int new;
	char *newstr;
	char *tmp;

	j = *i + 1;
	old = 0;
	new = 0;
	while (output->str[j] != output->quote)
		j++;
	printf("i: %d, j: %d\n", *i, j);
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
	tmp = output->str;
	output->str = newstr;
	free(tmp);
	*i = j - 1; 
	return (1);
}

int		clear_quotes(t_newstr *output)
{
	int i;
	
	i = 0;
	while(output->str[i])
	{
		if (output->str[i] == '$' && output->expand)
			// expand
		if (isquote(output->str[i]))
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

void	init_newstr(t_newstr *output, char *str)
{
	output->str = str;
	output->len = ft_strlen(str);
	output->expand = 1;
	output->open = 0;
	output->quote = '\0';
}

char	*clean_substring(char *str)
{
	t_newstr output;

	init_newstr(&output, str);
	if(!clear_quotes(&output))
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}	
	output.len = ft_strlen(output.str);
	return(output.str);
}
