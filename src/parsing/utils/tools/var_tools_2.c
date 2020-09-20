/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 20:42:14 by celestin          #+#    #+#             */
/*   Updated: 2020/09/20 21:06:10 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../incs/minishell.h"

char	*parsing_variable(t_parsing_tool *tool, char *str)
{
	t_list	*tmp;
	char	*output;
	int		len;

	len = ft_strlen(str);
	tmp = g_env;
	while (tmp)
	{
		if (!ft_strncmp(str, tmp->content, len) && tmp->content[len] == '=')
		{
			return (ft_strdup(&(tmp->content[len + 1])));
		}
		tmp = tmp->next;
	}
	tool->empty_var = 1;
	return (ft_strdup(""));
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

int		includes_var(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i > 0)
		{
			if (is_dollar(str[i]) && !is_backslash(str[i - 1]))
				return (1);
		}
		else
		{
			if (is_dollar(str[i]))
				return (1);
		}
		i++;
	}
	return (0);
}
