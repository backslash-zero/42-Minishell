/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 19:06:03 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/18 17:23:47 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		new_input_len(char *str, t_parsing_tool *tool)
{
	int len;
	int i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (test_empty_quote(str[i], str[i + 1]) && !tool->open)
			i += 2;
		else
		{
			if ((!test_empty_quote(str[i], str[i + 1]) && isquote(str[i]))
				|| (tool->open && str[i] == tool->quote))
				switcher_quote(tool, str[i]);
			i++;
			len++;
		}
	}
	if (tool->open)
		return (-1);
	return (len);
}

void	ft_copy_new_input(char *str, char *output, t_parsing_tool *tool)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (test_empty_quote(str[i], str[i + 1]) && !tool->open)
			i += 2;
		else
		{
			if ((!test_empty_quote(str[i], str[i + 1]) && isquote(str[i]))
				|| (tool->open && str[i] == tool->quote))
				switcher_quote(tool, str[i]);
			output[k] = str[i];
			k++;
			i++;
		}
	}
}

char	*ft_clean_input(char *str, t_parsing_tool *tool)
{
	char	*output;
	int		len;

	if ((len = new_input_len(str, tool)) == -1)
	{
		ft_error(SYNTAX_ERR, NULL, NULL, NULL);
		return (NULL);
	}
	if (!(output = malloc(sizeof(char) * len + 1)))
	{
		ft_strerror(NULL, NULL, NULL, NULL);
		return (NULL);
	}
	output[len] = '\0';
	ft_copy_new_input(str, output, tool);
	return (output);
}
