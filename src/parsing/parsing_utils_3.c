/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 19:08:29 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/07 00:51:07 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		is_redir_or_pipe(char c)
{
	if (is_pipe(c) ||
		is_redir_l(c) ||
		is_redir_r(c))
		return (1);
	else
		return (0);
}

int		is_pipe(char c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int		is_redir_l(char c)
{
	if (c == '<')
		return (1);
	else
		return (0);
}

int		is_redir_r(char c)
{
	if (c == '>')
		return (1);
	else
		return (0);
}

int		is_var(char *str)
{
	if (ft_strnstr(str, "$", ft_strlen(str)) != NULL)
		return (1);
	return (0);
}
