/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_funcs_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:18:16 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 19:55:49 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		is_redir_or_pipe(char c)
{
	if (is_pipe(c))
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
