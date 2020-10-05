/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 13:53:13 by rzafari           #+#    #+#             */
/*   Updated: 2020/08/19 13:53:41 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

int		arg_len(char **arg)
{
	int i;

	i = 0;
	if (arg)
		while (arg[i])
			i++;
	return (i);
}
