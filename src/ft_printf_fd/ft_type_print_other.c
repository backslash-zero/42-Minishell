/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_print_other.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 12:57:32 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	print_u(t_ftprint *p)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(p->list, unsigned int);
	if (p->flag_precision)
		p->flag_zero = 0;
	if (nb == 0 && p->flag_precision && p->field_precision == 0)
		print_d_zeroprec_zero(p);
	else
	{
		ft_get_nb_len_u(p, nb, 10);
		str = ft_nb_str_u(nb, p, 10, "0123456789");
		p->arg_len = p->nb_len;
		if (p->flag_precision && p->field_precision > p->nb_len)
			p->arg_len = p->field_precision;
		if (!p->flag_minus)
			ft_print_field_width(p);
		if (p->field_precision > p->nb_len && p->flag_precision)
			print_d_precision(p);
		ft_putstr_fd(p->fd, str);
		free(str);
		p->count += p->arg_len;
		if (p->flag_minus)
			ft_print_field_width(p);
	}
}

void	print_x_low(t_ftprint *p)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(p->list, unsigned int);
	if (p->flag_precision)
		p->flag_zero = 0;
	if (nb == 0 && p->flag_precision && p->field_precision == 0)
		print_d_zeroprec_zero(p);
	else
	{
		ft_get_nb_len_u(p, nb, 16);
		str = ft_nb_str_u(nb, p, 16, "0123456789abcdef");
		p->arg_len = p->nb_len;
		if (p->flag_precision && p->field_precision > p->nb_len)
			p->arg_len = p->field_precision;
		if (!p->flag_minus)
			ft_print_field_width(p);
		if (p->field_precision > p->nb_len && p->flag_precision)
			print_d_precision(p);
		ft_putstr_fd(p->fd, str);
		free(str);
		p->count += p->arg_len;
		if (p->flag_minus)
			ft_print_field_width(p);
	}
}

void	print_x_up(t_ftprint *p)
{
	unsigned int	nb;
	char			*str;

	nb = va_arg(p->list, unsigned int);
	if (p->flag_precision)
		p->flag_zero = 0;
	if (nb == 0 && p->flag_precision && p->field_precision == 0)
		print_d_zeroprec_zero(p);
	else
	{
		ft_get_nb_len_u(p, nb, 16);
		str = ft_nb_str_u(nb, p, 16, "0123456789ABCDEF");
		p->arg_len = p->nb_len;
		if (p->flag_precision && p->field_precision > p->nb_len)
			p->arg_len = p->field_precision;
		if (!p->flag_minus)
			ft_print_field_width(p);
		if (p->field_precision > p->nb_len && p->flag_precision)
			print_d_precision(p);
		ft_putstr_fd(p->fd, str);
		free(str);
		p->count += p->arg_len;
		if (p->flag_minus)
			ft_print_field_width(p);
	}
}

void	print_d(t_ftprint *p)
{
	int		nb;

	nb = va_arg(p->list, int);
	if (p->flag_precision)
		p->flag_zero = 0;
	if (nb == -2147483648)
		print_d_intmin(p);
	else if (nb < 0)
		print_d_negative(p, nb);
	else if (nb == 0 && p->flag_precision && p->field_precision == 0)
		print_d_zeroprec_zero(p);
	else
		print_d_default(p, nb);
}
