/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_funcs_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:50:35 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 20:34:52 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		is_redir_r(char c)
{
	if (c == '>')
		return (1);
	else
		return (0);
}

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	else
		return (0);
}

int		is_backslash(char c)
{
	if (c == '\\')
		return (1);
	else
		return (0);
}

int		is_bs_spec(char c)
{
	if (c == '$' || c == '\"' || c == '`' || c == '\\' || c == '\n')
		return (1);
	else
		return (0);
}
