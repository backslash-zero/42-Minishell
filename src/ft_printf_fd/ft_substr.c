/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:18:40 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"

char	*ft_substr(char const *s, unsigned int start, int len)
{
	int		i;
	char	*copy;

	i = 0;
	while (s[i + start] && i < len)
		i++;
	if (len > i)
		len = i;
	if (!(copy = (char *)malloc(len + 1)))
		return (NULL);
	i = -1;
	while (++i < len)
		copy[i] = s[start + i];
	copy[i] = '\0';
	return (copy);
}
