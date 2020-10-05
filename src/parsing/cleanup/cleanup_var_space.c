/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_var_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:14:22 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 12:38:00 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

int		create_new_arg_space(char **new_arg, char **arg, char **split_arg, int i)
{
	int	j;
	int	new_arg_pos;
	int len_split_arg;

	new_arg_pos = 0;
	len_split_arg = arg_len(split_arg);
	j = 0;
	while (j < i)
	{
		if (!(new_arg[new_arg_pos] = ft_strdup(arg[j])))
			return (0);
		new_arg_pos++;
		j++;
	}
	j = 0;
	while (j < len_split_arg)
	{
		if (!(new_arg[new_arg_pos] = ft_strdup(split_arg[j])))
			return (0);
		new_arg_pos++;
		j++;
	}
	j = i + 1;
	while (arg[j])
	{
		if (!(new_arg[new_arg_pos] = ft_strdup(arg[j])))
			return (0);
		j++;
		new_arg_pos++;
	}
	new_arg[new_arg_pos] = NULL;
	return (1);
}

static	int		reassign_space(t_cmd *cmd, int i)
{
	char	**split_arg;
	char	**new_arg;
	char	**tmp;

	tmp = cmd->arg;
	if (!(split_arg = parsing(tmp[i])))
		return (0);
	if (!(new_arg = malloc(sizeof(char *) * (arg_len(tmp) + arg_len(split_arg) - 1 + 1))))
		return (0);
	if (!(create_new_arg_space(new_arg, tmp, split_arg, i)))
		return (0);
	cmd->arg = new_arg;
	free_tab(split_arg);
	free_tab(tmp);
	return (1);
}

static	int		check_lonely_space(char *str)
{
	int				i;
	t_parsing_tool	tool;

	i = 0;
	init_tool(&tool);
	tool.input = str;
	while (tool.input[i])
	{
		if (is_quote(tool.input[i]))
			switcher_quote(&tool, i);
		if (!tool.open && is_space(tool.input[i]))
			return (1);
		i++;
	}
	return (0);
}

static int		check_space_args(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (check_lonely_space(arg[i]))
			return (i);
		i++;
	}
	return (-1);
}

int		check_space_var(t_cmd *cmd)
{
	int		index_space;

	while ((index_space = check_space_args(cmd->arg)) != -1)
	{
		if (!(reassign_space(cmd, index_space)))
			return (0);
	}
	return (1);
}
