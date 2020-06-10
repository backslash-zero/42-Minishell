/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:42:35 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdlib.h>

int		ft_putnbr_hex_len(t_ftprint *p, size_t nb, char *base)
{
	int		len;

	len = 1;
	if (nb < 16 && nb > 0)
		ft_putchar_fd(p->fd, base[nb]);
	else if (nb > 0)
	{
		len += ft_putnbr_hex_len(p, nb / 16, base);
		ft_putnbr_hex_len(p, nb % 16, base);
	}
	else if (nb == 0)
		ft_putchar_fd(p->fd, base[nb]);
	return (len);
}

char	*ft_nb_str(int nb, t_ftprint *p)
{
	char	*str;
	int		i;

	if (!(str = malloc((p->nb_len + 1) * sizeof(char))))
		return (NULL);
	i = p->nb_len;
	str[i] = '\0';
	if (nb == 0)
		str[0] = '0';
	if (nb < 0)
	{
		str[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		i--;
		str[i] = '0' + (nb % 10);
		nb /= 10;
	}
	return (str);
}

char	*ft_nb_str_u(unsigned int nb, t_ftprint *p, int b_l, char *b)
{
	char	*str;
	int		i;

	if (!(str = malloc((p->nb_len + 1) * sizeof(char))))
		return (NULL);
	i = p->nb_len;
	str[i] = '\0';
	if (nb == 0)
		str[0] = '0';
	while (nb > 0)
	{
		i--;
		str[i] = b[nb % b_l];
		nb /= b_l;
	}
	return (str);
}

void	ft_get_nb_len(t_ftprint *p, int nb, int base_len)
{
	int len;

	len = 0;
	if (nb == 0)
		p->nb_len = 1;
	else
	{
		while (nb != 0)
		{
			len++;
			nb /= base_len;
		}
		p->nb_len = len;
	}
}

void	ft_get_nb_len_u(t_ftprint *p, unsigned int nb, int base_len)
{
	int len;

	len = 0;
	if (nb == 0)
		p->nb_len = 1;
	else
	{
		if (nb < 0)
			p->nb_len = 1;
		while (nb != 0)
		{
			len++;
			nb /= base_len;
		}
		p->nb_len = len;
	}
}
