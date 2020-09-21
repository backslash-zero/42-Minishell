/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reads_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celestin <celestin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 00:53:51 by celestin          #+#    #+#             */
/*   Updated: 2020/09/22 01:00:57 by celestin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	get_len_semic(char **arg, int *i, int *len_new_arg_list)
{
	*len_new_arg_list = 0;
	while (*i < arg_len(arg) && ft_strcmp(arg[*i], ";") != 0)
	{
		*len_new_arg_list++;
		*i++;
	}
}
