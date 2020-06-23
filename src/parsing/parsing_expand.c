/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:40:30 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/23 17:39:15 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void 	switcher_expand(t_newstr *output, char c)
{
	if (output->open && c == output->quote)
	{
		output->open = 0;
		output->quote = '\0';
		output->expand = 0;
	}
	if (!output->open)
	{
		output->open = 1;
		output->quote = c;
		if (c == '\'')
			output->expand = 0;
	}
}

char	get_var(t_newstr *output, int i, int j)
{
		int len_var;
		int count;
		char *str;

		len_var = i - j;
		count = 0;
		if (!(str = malloc(sizeof(char) * (len_var + 1))))
			return (NULL);
		while (i < j)
		{
			str[count] = output->str[i];
			i++;
			count++;
		}
}


int		expand_str(t_newstr *output, int *i)
{
	int j;
	int len_remove;
	int len_add;
	char *newstr;

	*i++;
	j = *i;
	while (output->str[j] && output->str[j] != ' ' && !is_quote(output->str[j]))
		j++;
	// if (ft_strcmp(get_var, XXX))

}

int		expand_env(t_newstr *output)
{
	int i;

	i = 0;
	while (output->str[i])
	{
		if (is_quote(output->str[i]))
			switcher_expand(output, output->str[i]);
		if (output->str[i] == '$' && output->expand)
		{
			if(!expand_str(output, &i))
				return (0);
		}
		i++;
	}
}
