/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_var_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 17:14:22 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 01:50:05 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

static void		printtab(char **arg)
{
	int i = 0;
	while (arg[i])
	{
		printf("str-%d	%s\n", i, arg[i]);
		i++;
	}
}

static	int		create_new_arg_space(char **new_arg, char **arg, char **split_arg, int i)
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

static	int		reassign_space(char ***arg, int i)
{
	char	**split_arg;
	char	**new_arg;
	char	**tmp;

	tmp = *arg;
	if (!(split_arg = parsing(tmp[i])))
		return (0);
	printf("split\n");
	printtab(split_arg);
	if (!(new_arg = malloc(sizeof(char *) * (arg_len(tmp) + arg_len(split_arg) - 1 + 1))))
		return (0);
	if (!(create_new_arg_space(new_arg, tmp, split_arg, i)))
		return (0);
	printf("new arg\n");
	printtab(new_arg);
	assign_and_free_3(&new_arg, arg);
	printf("assign and free\n");
	free_tab(split_arg);
	printf("after free\n");
	printf("after free\n");
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

int		check_space_var(char ***arg)
{
	int		index_space;

	while ((index_space = check_space_args(*arg)) != -1)
	{
		printf("entered index space\n");
		if (!(reassign_space(arg, index_space)))
			return (0);
	}
	printf("exiting\n");
	return (1);
}
