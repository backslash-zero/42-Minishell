/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 11:37:30 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	ft_key(t_ftprint *p)
{
	ft_test_flags(p);
	if (p->str[p->i] == 's')
		print_s(p);
	else if (p->str[p->i] == 'c' || p->str[p->i] == '%')
		print_c(p);
	else if (p->str[p->i] == 'p')
		print_p(p);
	else if (p->str[p->i] == 'd' || p->str[p->i] == 'i')
		print_d(p);
	else if (p->str[p->i] == 'u')
		print_u(p);
	else if (p->str[p->i] == 'x')
		print_x_low(p);
	else if (p->str[p->i] == 'X')
		print_x_up(p);
}

int		ft_printf_fd(int fd, const char *format, ...)
{
	t_ftprint pf;

	pf = (t_ftprint) { .str = (char *)format };
	pf.fd = fd;
	va_start(pf.list, format);
	while (pf.i < (int)ft_strlen(format))
	{
		if (pf.str[pf.i] == '%')
		{
			pf.i++;
			ft_key(&pf);
		}
		else
		{
			ft_putchar_fd(pf.fd, pf.str[pf.i]);
			pf.count++;
		}
		if (pf.str[pf.i] != '\0')
			pf.i++;
		ft_reset_struct(&pf);
	}
	va_end(pf.list);
	return (pf.count);
}
