/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 11:18:58 by cmeunier          #+#    #+#             */
/*   Updated: 2020/07/21 11:19:28 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minishell.h"

void	ft_strncpy(char *dest, char *src, int len)
{
	int j;

	j = 0;
	while (j < len && src[j])
	{
		dest[j] = src[j];
		j++;
	}
}
