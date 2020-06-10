/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:42:35 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdlib.h>

void		ft_putnbr_hex(size_t nb)
{
	char	*base;

	base = "0123456789abcdef";
	if (nb <= 16 && nb > 0)
		ft_putchar_fd(p->fd, base[nb]);
	else if (nb > 0)
	{
		ft_putnbr_hex(nb / 16);
		ft_putnbr_hex(nb % 16);
	}
	else if (nb == 0)
		ft_putchar_fd(p->fd, base[nb]);
}
