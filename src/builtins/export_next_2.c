/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_next_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 12:01:00 by rzafari           #+#    #+#             */
/*   Updated: 2020/09/16 12:07:15 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		add_elem(char *s)
{
	if (!add_to_list(s, &g_export))
		return (0);
	if (ft_strchr(s, '='))
	{
		if (!add_to_list(s, &g_env))
			return (0);
	}
	return (1);
}

int		replace_elem(char *s, int i)
{
	char *s1;

	if (ft_strchr(s, '='))
	{
		s1 = ft_substr(s, 0, i);
		if (set_value(g_export, s, s1))
		{
			if (!set_value(g_env, s, s1))
			{
				if (!add_to_list(s, &g_env))
					return (0);
			}
			free(s1);
		}
		else
		{
			free(s1);
			return (0);
		}
	}
	return (1);
}
