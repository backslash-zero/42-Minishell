/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 19:05:26 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/24 18:41:03 by cmeunier         ###   ########.fr       */
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

char	*get_var_name(t_parsing_tool *tool, int i)
{
	int		j;
	int		k;
	char	*env_name;

	i++;
	j = i;
	if (envvar_authorized_character(tool->input[j], TRUE))
	{
		while (envvar_authorized_character(tool->input[j], FALSE))
			j++;
	}
	if (!(env_name = malloc(sizeof(char) * (j - i + 1))))
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
