/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_field_width.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:15:16 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	ft_test_size(t_ftprint *p)
{
	int value;

	value = 0;
	while (p->str[p->i] >= '0' && p->str[p->i] <= '9')
	{
		value *= 10;
		value += p->str[p->i] - 48;
		p->i++;
	}
	p->field_width = value;
}

void	ft_size_flagstar(t_ftprint *p)
{
	int value;

	value = 0;
	value = va_arg(p->list, int);
	if (value < 0)
	{
		p->field_width = -value;
		p->flag_minus = 1;
		if (p->flag_zero)
			p->flag_zero = 0;
	}
	else
		p->field_width = value;
	p->i++;
}

void	ft_size_default(t_ftprint *p)
{
	int value;

	value = 0;
	while (p->str[p->i] >= '0' && p->str[p->i] <= '9')
	{
		value *= 10;
		value += p->str[p->i] - 48;
		p->i++;
	}
	p->field_width = value;
}

void	ft_tests_checks(t_ftprint *p)
{
	if (p->flag_precision)
		ft_print_precision(p);
	else
		ft_print_field_width(p);
}

void	ft_print_field_width(t_ftprint *p)
{
	char padding_char;

	padding_char = ' ';
	if (p->str[p->i] != 'd' ||
			p->str[p->i] != 'i' ||
			p->str[p->i] != 'u' ||
			p->str[p->i] != 'x' ||
			p->str[p->i] != 'X')
	{
		if (p->flag_zero == 1)
			padding_char = '0';
	}
	while (p->field_width - p->arg_len > 0)
	{
		ft_putchar_fd(p->fd, padding_char);
		p->count++;
		p->field_width--;
	}
}
