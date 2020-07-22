/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_substring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 18:08:32 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/22 13:37:52 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		append_semicolon(int *i, int *j, int *n, t_parsing_tool *tool)
{
	char *newstr;

	if (is_semic(tool->input[*i]))
	{
		if (!(tool->arg[*n] = malloc(sizeof(char) * 2)))
			return (0);
		tool->arg[*n][0] = ';';
		tool->arg[*n][1] = '\0';
		*i = *j;
		*n += 1;
	}
	return (1);
}


int		append_string_to_arg(int *i, int *j, int *n, t_parsing_tool *tool)
{
	if (*j - *i > 0)
	{
		if (!(tool->arg[*n] = ft_addsubstr(*i, *j, tool)))
		{
			ft_strerror(NULL, NULL, NULL, NULL);
			return (0);
		}
		*i = *j;
		*n += 1;
	}
	return (1);
}

char	*ft_addsubstr(int i, int j, t_parsing_tool *tool)
{
	int		len;
	char	*str;

	len = j - i + 1;
	if (!(str = malloc(sizeof(char) * (len))))
		return (NULL);
	len = 0;
	while (i < j)
	{
		str[len] = tool->input[i];
		i++;
		len++;
	}
	str[len] = '\0';
	return (clean_substring(str));
}
