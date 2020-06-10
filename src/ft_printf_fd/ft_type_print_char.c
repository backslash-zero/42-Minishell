/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_print_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:57:32 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	ft_printstring(t_ftprint *p, char *str)
{
	if (!(p->field_precision == 0 && p->flag_precision))
		ft_putstr_fd(p->fd, str);
}

void	print_s_null(t_ftprint *p)
{
	char *s;

	s = "(null)";
	p->arg_len = ft_strlen(s);
	if (p->field_precision < (int)ft_strlen(s) && p->flag_precision)
		p->arg_len = p->field_precision;
	if (!p->flag_minus)
		ft_print_field_width(p);
	if (p->field_precision < (int)ft_strlen(s) && p->flag_precision)
	{
		s = ft_substr(s, 0, p->field_precision);
		ft_printstring(p, s);
		free(s);
	}
	else
		ft_printstring(p, s);
}

void	print_s(t_ftprint *p)
{
	char *s;

	s = va_arg(p->list, char *);
	if (!s)
		print_s_null(p);
	else
	{
		p->arg_len = ft_strlen(s);
		if (p->field_precision < (int)ft_strlen(s) && p->flag_precision)
			p->arg_len = p->field_precision;
		if (!p->flag_minus)
			ft_print_field_width(p);
		if (p->field_precision < (int)ft_strlen(s) && p->flag_precision)
		{
			s = ft_substr(s, 0, p->field_precision);
			ft_printstring(p, s);
			free(s);
		}
		else
			ft_printstring(p, s);
	}
	if (p->flag_minus)
		ft_print_field_width(p);
	p->count += p->arg_len;
}

void	print_c(t_ftprint *p)
{
	char c;

	p->arg_len = 1;
	if (!p->flag_minus)
		ft_print_field_width(p);
	if (p->str[p->i] == '%')
		ft_putchar_fd(p->fd, '%');
	else
	{
		c = (char)va_arg(p->list, int);
		ft_putchar_fd(p->fd, c);
	}
	if (p->flag_minus)
		ft_print_field_width(p);
	p->count += 1;
}

void	print_p(t_ftprint *p)
{
	void	*str;
	size_t	address;
	size_t	copy;

	str = va_arg(p->list, void *);
	address = (size_t)str;
	copy = address;
	if (copy == 0)
		p->nb_len++;
	while (copy != 0)
	{
		p->nb_len++;
		copy /= 16;
	}
	p->nb_len += 2;
	p->arg_len = p->nb_len;
	if (!p->flag_minus)
		ft_print_field_width(p);
	ft_putstr_fd(p->fd, "0x");
	ft_putnbr_hex_len(p, address, "0123456789abcdef");
	if (p->flag_minus)
		ft_print_field_width(p);
	p->count += p->arg_len;
}
