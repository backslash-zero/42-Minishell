/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:17:43 by celestin          #+#    #+#             */
/*   Updated: 2020/09/18 10:40:15 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

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
