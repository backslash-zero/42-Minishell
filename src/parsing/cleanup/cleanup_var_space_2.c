/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_var_space_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 15:35:03 by celestin          #+#    #+#             */
/*   Updated: 2020/10/05 16:03:10 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incs/minishell.h"

static void	init_copy_arg2arg(int *j, int *new_pos, int *len, char **split)
{
	*j = 0;
	*new_pos = 0;
	*len = arg_len(split);
}

static int	copy_arg2arg(int *j, int *new_pos, char **new_arg, char **src)
{
	if (!(new_arg[*new_pos] = ft_strdup(src[*j])))
		return (0);
	*new_pos += 1;
	*j += 1;
	return (1);
}

int			create_new_arg_space(char **new, char **arg, char **split, int i)
{
	int	j;
	int	new_arg_pos;
	int len_split_arg;

	init_copy_arg2arg(&j, &new_arg_pos, &len_split_arg, split);
	while (j < i)
	{
		if (!copy_arg2arg(&j, &new_arg_pos, new, arg))
			return (0);
	}
	j = 0;
	while (j < len_split_arg)
	{
		if (!copy_arg2arg(&j, &new_arg_pos, new, split))
			return (0);
	}
	j = i + 1;
	while (arg[j])
	{
		if (!copy_arg2arg(&j, &new_arg_pos, new, arg))
			return (0);
	}
	new[new_arg_pos] = NULL;
	return (1);
}
