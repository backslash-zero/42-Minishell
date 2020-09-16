/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 17:17:43 by celestin          #+#    #+#             */
/*   Updated: 2020/09/16 13:21:54 by celestin         ###   ########.fr       */
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
			printf("error here 1\n");
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

	i = 0;
	count = 0;
	n = 1;
	while (str[i])
	{
		if (i > 0)
		{
			if (is_backslash(str[i]) && n)
			{
				count++;
				n = 0;
			}
			else
			{
				n = 1;
			}
		}
		else
		{
			if (is_backslash(str[i]))
			{
				count++;
				n = 0;
			}
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
	printf("new_len_backslash(arg_list[a]): %d\n", new_len_backslash(arg_list[a]));
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
	printf("new str: %s\n", newstr);
	assign_and_free(&newstr, &arg_list[a]);
	printf("arg_list[a] str: %s\n", arg_list[a]);
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