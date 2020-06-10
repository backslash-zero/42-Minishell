/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:42:35 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdlib.h>

int		ft_putnbr_hex_len(size_t nb, char *base)
{
	int		len;

	len = 1;
	if (nb <= 16 && nb > 0)
		ft_putchar(base[nb]);
	else if (nb > 0)
	{
		len += ft_putnbr_hex_len(nb / 16, base);
		ft_putnbr_hex_len(nb % 16, base);
	}
	else if (nb == 0)
		ft_putchar(base[nb]);
	return (len);
}
