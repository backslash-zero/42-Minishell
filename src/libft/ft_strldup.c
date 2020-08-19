/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strldup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:21:33 by cmeunier          #+#    #+#             */
/*   Updated: 2020/08/19 14:22:16 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strldup(const char *s1, int start, int end)
{
	char	*s2;
	int		j;

	j = 0;
	if (!(s2 = (char *)malloc(sizeof(char) * ((end - start) + 3))))
		return (NULL);
	while (start < end + 1)
	{
		s2[j] = s1[start];
		start++;
		j++;
	}
	s2[j++] = '/';
	s2[j] = '\0';
	return (s2);
}
