/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:17:43 by celestin          #+#    #+#             */
/*   Updated: 2020/09/16 17:54:21 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		is_backslash(char c)
{
	if (c == '\\')
		return (1);
	else
		return (0);
}

int		check_backslash(char *str)
{
	int i;
	int bs_count;

	i = 0;
	bs_count = 0;
	while (str[i])
	{
		while (is_backslash(str[i]))
		{
			bs_count++;
			i++;
		}
		if (bs_count % 2 != 0 && bs_count != 1 && (is_space(str[i]) || !str[i]))
		{
			return (-1);
		}
		bs_count = 0;
		if (!str[i])
			return (0);
		i++;
	}
	return (0);
}

int		new_len_backslash(char *str)
{
	int i;
	int count;
	int n;

	i = 1;
	count = 0;
	n = 1;

	while (str[i])
	{
		if (is_backslash(str[i - 1]) && n)
		{	
			count++;
			if (is_backslash(str[i]))
				n = 0;
		}
		else
		{
			n = 1;
		}
		i++;
	}
	return (ft_strlen(str) - count);
}

int		ft_clean_backslash(char **arg_list, int a)
{
	int		i;
	int		j;
	char	*newstr;

	i = 0;
	j = 0;
	if(!(newstr = malloc(sizeof(char) * (new_len_backslash(arg_list[a]) + 1))))
		return (0);
	while (arg_list[a][i])
	{
		if (is_backslash(arg_list[a][i]))
		{
			i++;
		}
		if (arg_list[a][i] != '\0')
		{
			newstr[j] = arg_list[a][i];
			i++;
			j++;
		}
	}
	newstr[j] = '\0';
	assign_and_free(&newstr, &arg_list[a]);
	return (1);
}

int		ft_backslash(char **arg_list)
{
	int	i;

	i = 0;
	while (arg_list[i])
	{
		if (ft_strrchr(arg_list[i], '\\'))
		{
			if (!ft_clean_backslash(arg_list, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int		check_bf_bs(char *str, int i)
{
	if (i == 0)
		return (0);
	else
	{
		if (is_backslash(str[i - 1]))
			return (1);
	}
	return (0);
}