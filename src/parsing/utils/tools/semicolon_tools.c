/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:27:42 by celestin          #+#    #+#             */
/*   Updated: 2020/09/21 13:43:44 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		semic_checker(t_parsing_tool *tool, int i, int *n)
{
	if (is_semic(tool->input[i]) && !tool->open)
	{
		if (i > 0)
		{
			if (!is_backslash(tool->input[i - 1]))
				*n = 2;
			if (i == 1)
			{
				if (is_semic(tool->input[i - 1]) && !tool->open)
					return (-1);
			}
			if (i > 1)
			{				
				if (is_semic(tool->input[i - 1])
					&& !is_backslash(tool->input[i - 2]) && !tool->open)
					return (-1);
			}
		}
		if (i == 0)
			return (-1);
	}
	return (0);
}
