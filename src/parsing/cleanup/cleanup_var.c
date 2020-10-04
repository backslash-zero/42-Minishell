/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 19:59:05 by celestin          #+#    #+#             */
/*   Updated: 2020/10/04 18:57:07 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		check_emptyarg_redir(t_parsing_tool *tool, int tab_i)
{
	if (tab_i > 0)
	{
		if (arg_is_redir(tool->arg[tab_i - 1]))
			return (1);
	}
	return (0);
}

int		insert_env_var(t_parsing_tool *tool, int i, int tab_i)
{
	char	*env_name;
	char	*var;

	if (!(env_name = get_var_name(tool, i)))
		return (0);
	if (!(var = parsing_variable(tool, env_name)))
		return (0);
	if (tool->empty_var)
	{
		if (check_emptyarg_redir(tool, tab_i))
		{
			free(env_name);
			free(var);
			return (-2);
		}
		remove_var(tool, i, env_name);
		tool->empty_var = 0;
	}
	else
		rplc_vr(tool, i, var, env_name);
	free(env_name);
	free(var);
	return (1);
}

int		conditions_expand_env(t_parsing_tool *tool, int i)
{
	if (is_dollar(tool->input[i])
		&& !(tool->open && tool->quote == '\'')
		&& !test_lone_dollar(tool->input, i)
		&& (tool->input[i + 1] != '?'))
		return (1);
	return (0);
}

int		expand_env(t_parsing_tool *tool, int tab_i)
{
	int i;
	int ret;
	int new_insert;

	i = 0;
	while (tool->input[i])
	{
		new_insert = 0;
		bs_checker(tool, i);
		if (is_quote(tool->input[i]))
			switcher_quote(tool, i);
		else if (conditions_expand_env(tool, i) && (!tool->pre_bs))
		{
			if ((ret = insert_env_var(tool, i, tab_i)) < 1)
				return (ret);
			i = (i > 0) ? i-- : i;
			new_insert = 1;
		}
		cancel_pre_bs(tool, i);
		if (tool->input[i] && !new_insert)
			i++;
	}
	return (1);
}

int		check_var(char **arg_list)
{
	int				i;
	int				ret;
	t_parsing_tool	tool;

	init_tool(&tool);
	tool.arg = arg_list;
	i = 0;
	while (arg_list[i])
	{
		if (includes_var(arg_list[i]))
		{
			init_tool(&tool);
			tool.input = ft_strdup(arg_list[i]);
			if ((ret = expand_env(&tool, i)) < 1)
			{
				assign_and_free(&tool.input, &arg_list[i]);
				return (ret);
			}
			assign_and_free(&tool.input, &arg_list[i]);
		}
		i++;
	}
	return (1);
}
