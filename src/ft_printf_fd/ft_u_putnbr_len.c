/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_putnbr_len.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:42:35 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 22:10:15 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdlib.h>

int		ft_u_putnbr_len(t_ftprint *p, unsigned int nb)
{
	int		len;

	len = 1;
	if (nb < 0)
	{
		ft_putchar_fd(p->fd, '-');
		nb = -nb;
		len++;
	}
	if (nb <= 9 && nb > 0)
		ft_putchar_fd(p->fd, nb + '0');
	else if (nb > 0)
	{
		len += ft_putnbr_len(nb / 10);
		ft_putnbr_len(nb % 10);
	}
	else if (nb == 0)
		ft_putchar_fd(p->fd, '0');
	return (len);
}
