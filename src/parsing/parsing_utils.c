/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 19:05:26 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/22 13:34:32 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	quote_checker(t_parsing_tool *tool, int i, int *n)
{
	if (is_quote(tool->input[i]))
	{
		switcher_quote(tool, tool->input[i]);
		if (!tool->open)
			*n = 0;
	}
}

int		semic_checker(t_parsing_tool *tool, int i, int *n)
{
	if (is_semic(tool->input[i]) && !tool->open)
	{
		*n = 1;
		if (i > 0)
		{
			if (is_semic(tool->input[i - 1]) && !tool->open)
				return (-1);
		}
		if (i == 0)
			return (-1);
	}
	return (0);
}

char	*get_var_name(t_parsing_tool *tool, int i)
{
	int		j;
	int		k;
	char	*env_name;

	i++;
	j = i;
	k = 0;
	while (tool->input[j] && !is_space(tool->input[j])
		&& !is_quote(tool->input[j]) && !is_dollar(tool->input[j])
		&& !is_equal(tool->input[j]))
	{
		j++;
		k++;
	}
	if (!(env_name = malloc(sizeof(char) * (k + 1))))
		return (NULL);
	k = 0;
	while (i < j)
	{
		env_name[k] = tool->input[i];
		i++;
		k++;
	}
	env_name[k] = '\0';
	return (env_name);
}

char	*parsing_variable(t_parsing_tool *tool, char *str)
{
	t_list	*tmp;
	char	*output;
	int		len;

	len = ft_strlen(str);
	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->content, len))
		{
			return (ft_strdup(&(tmp->content[len + 1])));
		}
		tmp = tmp->next;
	}
	tool->empty_var = 1;
	return (ft_strdup(""));
}
