/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 15:08:47 by cmeunier          #+#    #+#             */
/*   Updated: 2019/10/22 13:50:14 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*c_itoastr(char *str, int i, int n, int negative)
{
	str[i--] = '\0';
	while (n < 0)
	{
		str[i--] = '0' + (-(n % 10));
		n = n / 10;
	}
	if (negative)
		str[i] = '-';
	return (str);
}

static	int		c_len(int n, int negative)
{
	int len;

	len = 0;
	if (n == 0)
	{
		len = 1;
		return (len);
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	if (negative == 1)
		len++;
	return (len);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		negative;
	int		len;

	negative = 1;
	i = 0;
	if (n > 0)
	{
		negative = 0;
		n = -n;
	}
	len = c_len(n, negative);
	if (!(str = malloc(sizeof(char) * len + 1)))
		return (NULL);
	if (n == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	i = len;
	return (c_itoastr(str, i, n, negative));
}
