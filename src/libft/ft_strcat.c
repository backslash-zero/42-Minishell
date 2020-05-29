/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 01:07:41 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/28 01:48:54 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_strcat(char *s1, const char *s2)
{
    int		i;
    int		j;
    
	i = 0;
	j = 0;
	while(s1[i])
		i++;
	while(s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = '\0';
	return(s1);
}
