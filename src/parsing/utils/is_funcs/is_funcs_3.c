/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_funcs_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:50:31 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 20:03:12 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		is_space(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int		is_equal(char c)
{
	if (c == '=')
		return (1);
	else
		return (0);
}

int		is_semic(char c)
{
	if (c == ';')
		return (1);
	else
		return (0);
}

int		test_lone_dollar(char *str, int i)
{
	if (!envvar_authorized_character(str[i + 1], TRUE))
		return (1);
	return (0);
}

int		is_dollar(char c)
{
	if (c == '$')
		return (1);
	else
		return (0);
}
