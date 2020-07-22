/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:16:10 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/21 18:20:21 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		insert_ret(t_parsing_tool *tool, int i)
{
	char	*newstr;
	int		j;
	int		k;
	char	*ret;

	k = i;
	j = 0;
	ret = ft_itoa(g_ret);
	if (!(newstr = malloc(sizeof(char) *
		(i + ft_strlen(ret) - (ft_strlen(tool->input) - i - 2) + 1))))
		return (0);
	ft_strncpy(newstr, tool->input, i);
	ft_strncpy(&newstr[i], ret, ft_strlen(ret));
	i = i + ft_strlen(ret);
	j = k + 2;
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	assign_and_free(&newstr, &tool->input);
	return (1);
}

int		expand_env(t_parsing_tool *tool)
{
	int i;

	i = 0;
	while (tool->input[i])
	{
		if (is_quote(tool->input[i]))
			switcher_quote(tool, tool->input[i]);
		if (tool->input[i + 1] == '?')
		{
			if (!insert_ret(tool, i))
				return (-1);
		}
		else if (is_dollar(tool->input[i])
			&& !(tool->open && tool->quote == '\'')
			&& !test_lone_dollar(tool->input, i))
		{
			if (!insert_env_var(tool, i))
				return (-1);
		}
		i++;
	}
	return (0);
}

int		remove_var(t_parsing_tool *tool, int i, char *env_name)
{
	char	*newstr;
	int		len_newstr;
	int		j;

	tool->empty_var = 0;
	j = 0;
	len_newstr = ft_strlen(tool->input) - (ft_strlen(env_name) + 1);
	if (!(newstr = malloc(sizeof(char) * (len_newstr + 1))))
		return (0);
	ft_strncpy(newstr, tool->input, i);
	j = i + 1 + ft_strlen(env_name);
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	assign_and_free(&newstr, &tool->input);
	return (1);
}

int		replace_var(t_parsing_tool *tool, int i, char *var, char *env_name)
{
	char	*newstr;
	int		j;
	int		k;

	k = i;
	j = 0;
	if (!(newstr = malloc(sizeof(char) *
		(calc_len_newstr(var, tool->input, env_name, i) + 1))))
		return (0);
	ft_strncpy(newstr, tool->input, i);
	ft_strncpy(&newstr[i], var, ft_strlen(var));
	i = i + ft_strlen(var);
	j = k + ft_strlen(env_name) + 1;
	while (tool->input[j])
	{
		newstr[i] = tool->input[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	assign_and_free(&newstr, &tool->input);
	return (1);
}

int		insert_env_var(t_parsing_tool *tool, int i)
{
	char *env_name;
	char *var;

	if (!(env_name = get_var_name(tool, i)))
		return (0);
	if (!(var = parsing_variable(tool, env_name)))
		return (0);
	if (tool->empty_var)
		remove_var(tool, i, env_name);
	else
		replace_var(tool, i, var, env_name);
	free(env_name);
	free(var);
	return (1);
}
