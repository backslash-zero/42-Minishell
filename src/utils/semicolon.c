/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:59:56 by rzafari           #+#    #+#             */
/*   Updated: 2020/08/19 14:01:09 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

char	**semicolon(char **arg, int i, int len_new_arg_list)
{
	char	**arg_list;
	int		j;
	int		n;

	j = 0;
	if (!(arg_list = malloc(sizeof(char *) * (len_new_arg_list + 1))))
		return (NULL);
	n = i - len_new_arg_list;
	while (j < len_new_arg_list)
	{
		arg_list[j] = ft_strdup(arg[n]);
		j++;
		n++;
	}
	arg_list[j] = NULL;
	return (arg_list);
}
