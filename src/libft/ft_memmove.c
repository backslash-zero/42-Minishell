/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:19:18 by cmeunier          #+#    #+#             */
/*   Updated: 2019/10/24 16:11:39 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*dest;
	const char	*source;
	char		*enddest;
	const char	*endsource;

	if (dst == src)
		return (dst);
	dest = dst;
	source = src;
	enddest = dest + (n - 1);
	endsource = source + (n - 1);
	if (dest < source)
	{
		while (n--)
			*dest++ = *source++;
	}
	else
	{
		while (n--)
			*enddest-- = *endsource--;
	}
	return (dst);
}
