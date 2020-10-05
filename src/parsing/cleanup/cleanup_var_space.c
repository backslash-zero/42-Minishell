/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_var_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:14:22 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 16:07:35 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

static	int		reassign_space(t_cmd *cmd, int i)
{
	char	**split_arg;
	char	**new_arg;
	char	**tmp;

	tmp = cmd->arg;
	if (!(split_arg = parsing(tmp[i])))
		return (0);
	if (!(new_arg = malloc(sizeof(char *) *
		(arg_len(tmp) + arg_len(split_arg) - 1 + 1))))
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

int				check_space_var(t_cmd *cmd)
{
	int		index_space;

	while ((index_space = check_space_args(cmd->arg)) != -1)
	{
		if (!(reassign_space(cmd, index_space)))
			return (0);
	}
	return (1);
}
