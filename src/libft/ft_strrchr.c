/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 10:28:36 by cmeunier          #+#    #+#             */
/*   Updated: 2019/10/24 16:54:54 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char *str;
	char *last;

	str = (char*)s;
	last = 0;
	while (*str)
	{
		if (c == *str)
			last = str;
		str++;
	}
	if (c == '\0')
		return (str);
	return (last);
}
