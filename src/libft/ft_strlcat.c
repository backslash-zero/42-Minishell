/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:07:40 by cmeunier          #+#    #+#             */
/*   Updated: 2020/05/27 14:31:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	i;
	size_t	len;
	char	*dest2;
	char	*src2;

	src2 = src;
	dest2 = dest;
	i = 0;
	while (i++ < size && *dest2 != '\0')
		dest2++;
	len = dest2 - dest;
	if (size - len == 0)
		return (len + ft_strlen(src));
	i = len;
	while (*src2 != '\0')
	{
		if (i++ < size - 1)
		{
			*dest2 = *src2;
			dest2++;
		}
		src2++;
	}
	*dest2 = '\0';
	return (len + src2 - src);
}
