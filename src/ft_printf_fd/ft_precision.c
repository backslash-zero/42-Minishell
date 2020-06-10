/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 23:54:49 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	print_d_precision(t_ftprint *p)
{
	while (p->field_precision > p->nb_len)
	{
		ft_putchar_fd(p->fd, '0');
		p->field_precision--;
	}
}

void	ft_test_precision(t_ftprint *p)
{
	if (p->str[p->i] == '.')
	{
		p->flag_precision = 1;
		p->i++;
		ft_getprecision(p);
	}
}

void	ft_getprecision(t_ftprint *p)
{
	int value;

	value = 0;
	if (p->str[p->i] == '*')
	{
		value = va_arg(p->list, int);
		if (value < 0)
		{
			p->field_precision = 0;
			p->flag_precision = 0;
		}
		else
			p->field_precision = value;
		p->i++;
	}
	else
		ft_precision_default(p);
}

void	ft_precision_default(t_ftprint *p)
{
	int value;

	value = 0;
	while (p->str[p->i] >= '0' && p->str[p->i] <= '9')
	{
		value *= 10;
		value += p->str[p->i] - 48;
		p->i++;
	}
	p->field_precision = value;
}

void	ft_print_precision(t_ftprint *p)
{
	if (p->str[p->i] == 'd' ||
			p->str[p->i] == 'i' ||
			p->str[p->i] == 'u' ||
			p->str[p->i] == 'x' ||
			p->str[p->i] == 'X')
	{
		while (p->field_precision - p->arg_len > 0)
		{
			ft_putchar_fd(p->fd, '0');
			p->count++;
			p->field_precision--;
		}
	}
}
