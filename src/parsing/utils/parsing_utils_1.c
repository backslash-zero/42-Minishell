/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:12:21 by celestin          #+#    #+#             */
/*   Updated: 2020/09/23 13:19:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

void	init_tool(t_parsing_tool *tool)
{
	tool->quote = '\0';
	tool->open = 0;
	tool->empty_var = 0;
	tool->pre_bs = 0;
	tool->expand = 0;
}

void	skipspaces(t_parsing_tool *tool, int *i, int *j)
{
	while (ft_is_space(tool->input[*i]))
	{
		*i += 1;
		*j += 1;
	}
}

int		envvar_authorized_character(char c, int first_char)
{
	if (first_char == TRUE)
		if (c == '_' || (c >= 65 && c <= 90) || (c >= 97 && c <= 122))
			return (TRUE);
	if (first_char == FALSE)
		if (c == '_' || (c > 64 && c < 91) || (c > 96 && c < 123) ||
			(c > 47 && c < 58))
			return (TRUE);
	return (FALSE);
}
