/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_pipe_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:44:14 by celestin          #+#    #+#             */
/*   Updated: 2020/09/21 13:41:12 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

int		redir_r_checker(t_parsing_tool *tool, int *i, int *n)
{
	int a;

	a = *i;
	if (is_redir_r(tool->input[a]) && !tool->open)
	{
		if (i == 0)
			return (-1);
		*n = 2;
		if (is_redir_r(tool->input[*i + 1]))
			*i += 1;
		a = *i;
		while (ft_is_space(tool->input[a + 1]))
			a++;
		if (is_redir_or_pipe(tool->input[a + 1])
			|| is_semic(tool->input[a + 1])
			|| !tool->input[a + 1])
			return (-1);
	}
	return (0);
}

int		redir_l_checker(t_parsing_tool *tool, int *i, int *n)
{
	int a;

	a = *i;
	if (is_redir_l(tool->input[a]) && !tool->open)
	{
		*n = 2;
		if (i == 0)
			return (-1);
		while (ft_is_space(tool->input[a + 1]))
			a++;
		if (is_redir_or_pipe(tool->input[a + 1])
			|| is_semic(tool->input[a + 1])
			|| !tool->input[a + 1])
			return (-1);
	}
	return (0);
}

int		pipe_checker(t_parsing_tool *tool, int i, int *n)
{
	if (is_pipe(tool->input[i]) && !tool->open)
	{
		*n = 2;
		if (i == 0)
			return (-1);
		while (ft_is_space(tool->input[i + 1]))
			i++;
		if (is_redir_or_pipe(tool->input[i + 1]) ||
		is_semic(tool->input[i + 1]) || !tool->input[i + 1])
			return (-1);
	}
	return (0);
}

int		redir_pipe_checker(t_parsing_tool *tool, int *i, int *n)
{
	if (*i > 0)
	{
		if (is_redir_or_pipe(tool->input[*i])
			&& is_backslash((tool->input[*i - 1])))
			return (0);
	}
	if (redir_r_checker(tool, i, n) || pipe_checker(tool, *i, n)
	|| redir_l_checker(tool, i, n))
		return (-1);
	return (0);
}
