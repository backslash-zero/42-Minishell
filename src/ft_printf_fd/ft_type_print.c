/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_print.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:57:32 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	print_s(t_ftprint *p)
{
	char *s;

	s = va_arg(p->list, char *);
	ft_putstr_fd(p->fd, s);
	p->count += ft_strlen(s);
}

void	print_c(t_ftprint *p)
{
	char c;

	if (p->str[p->i] == '%')
		ft_putchar('%');
	else
	{
		c = (char)va_arg(p->list, int);
		ft_putchar(c);
	}
	p->count++;
}

void	print_p(t_ftprint *p)
{
	void	*str;
	size_t	address;

	ft_putstr_fd(p->fd, "0x");
	str = va_arg(p->list, void *);
	address = (size_t)str;
	ft_putnbr_hex(address);
	p->count += 14;
}

void	print_d(t_ftprint *p)
{
	int d;

	d = va_arg(p->list, int);
	if (d != -2147483648)
		p->count += ft_putnbr_len(d);
	else
	{
		ft_putstr_fd(p->fd, "-2147483648");
		p->count += 11;
	}
}

void	print_u(t_ftprint *p)
{
	unsigned int u;

	u = (unsigned int)va_arg(p->list, unsigned int);
	p->count += ft_putnbr_len(u);
}
