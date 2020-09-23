/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:48:46 by celestin          #+#    #+#             */
/*   Updated: 2020/09/22 00:05:41 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

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

int		append_str2arg(int *i, int *j, int *n, t_parsing_tool *tool)
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

int		append_semicolon(int *i, int *j, int *n, t_parsing_tool *tool)
{
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

int		parsing_checks(int *i, int *j, int *n, t_parsing_tool *tool)
{
	if (!append_str2arg(i, j, n, tool))
		return (0);
	if (!append_semicolon(i, j, n, tool))
		return (0);
	if (!append_redir_pipe(i, j, n, tool))
		return (0);
	return (1);
}
