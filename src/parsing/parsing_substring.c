/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_substring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 18:08:32 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/19 11:14:19 by celestin         ###   ########.fr       */
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

int		append_redir_pipe(int *i, int *j, int *n, t_parsing_tool *tool)
{
	char	*newstr;
	int		len;

	len = 1;
	if (is_redir_or_pipe(tool->input[*i]))
	{
		if (is_redir_r(tool->input[*i + 1]))
		{
			len++;
			*j += 1;
		}
		if (!(tool->arg[*n] = malloc(sizeof(char) * len + 1)))
			return (0);
		tool->arg[*n][0] = tool->input[*i];
		tool->arg[*n][1] = tool->input[*i + 1];
		tool->arg[*n][len] = '\0';
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
	return (str);
}
