/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:16:10 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/20 13:19:09 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		conditions_expand_env(t_parsing_tool *tool, int i)
{
	if (is_dollar(tool->input[i])
		&& !(tool->open && tool->quote == '\'')
		&& !test_lone_dollar(tool->input, i)
		&& (tool->input[i + 1] != '?'))
		return (1);
	return (0);
}

int		expand_env(t_parsing_tool *tool)
{
	int i;

	i = 0;
	while (tool->input[i])
	{
		bs_checker(tool, i);
		if (is_quote(tool->input[i]))
			switcher_quote(tool, i);
		else if (conditions_expand_env(tool, i))
		{
			if (!tool->pre_bs)
			{
				if (!insert_env_var(tool, i))
					return (0);
				i--;
			}
		}
		cancel_pre_bs(tool, i);
		i++;
	}
	return (1);
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
	char	*env_name;
	char	*var;

	if (!(env_name = get_var_name(tool, i)))
		return (0);
	if (!(var = parsing_variable(tool, env_name)))
		return (0);
	if (tool->empty_var)
	{
		remove_var(tool, i, env_name);
		tool->empty_var = 0;
	}
	else
		replace_var(tool, i, var, env_name);
	free(env_name);
	free(var);
	return (1);
}

int		check_var(char **arg_list)
{
	int				i;
	t_parsing_tool	tool;

	i = 0;
	while (arg_list[i])
	{
		if (includes_var(arg_list[i]))
		{
			init_tool(&tool);
			tool.input = ft_strdup(arg_list[i]);
			if (!(expand_env(&tool)))
				return (0);
			assign_and_free(&tool.input, &arg_list[i]);
		}
		i++;
	}
	return (1);
}
