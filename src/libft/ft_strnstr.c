/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:22:56 by cmeunier          #+#    #+#             */
/*   Updated: 2019/10/24 16:27:56 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *nd, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (*nd == '\0')
		return ((char *)h);
	if (h == NULL && len == 0)
		return (0);
	while (*h != '\0' && l < len)
	{
		if (*h == nd[i])
		{
			while (h[i] == nd[i] && h[i] && i + l < len)
				i++;
			if (nd[i] == '\0')
				return ((char *)h);
			else
				i = 0;
		}
		h++;
		l++;
	}
	return (0);
}
