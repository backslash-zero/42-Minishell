/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_print_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:32:58 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 19:59:22 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"
#include <stdarg.h>

void	print_d_handle_flags(t_ftprint *p)
{
	if (p->flag_precision && p->field_precision > p->nb_len)
		p->arg_len = p->field_precision;
	if (p->nb_neg && p->flag_zero)
		ft_putchar_fd(p->fd, '-');
	if (!p->flag_minus)
		ft_print_field_width(p);
	if (p->nb_neg && !(p->flag_zero))
		ft_putchar_fd(p->fd, '-');
	if (p->field_precision > p->nb_len && p->flag_precision)
		print_d_precision(p);
}

void	print_d_negative(t_ftprint *p, int nb)
{
	char	*str;
	int		precision_copy;

	precision_copy = p->field_precision;
	p->nb_neg = 1;
	nb = -nb;
	ft_get_nb_len(p, nb, 10);
	str = ft_nb_str(nb, p);
	p->arg_len = p->nb_len + 1;
	if (p->field_width > 0
		&& p->flag_precision && p->field_precision > p->nb_len)
		p->field_width--;
	print_d_handle_flags(p);
	ft_putstr_fd(p->fd, str);
	free(str);
	if (p->flag_precision && precision_copy > p->nb_len)
		p->count += p->arg_len + 1;
	else
		p->count += p->arg_len;
	if (p->flag_minus)
		ft_print_field_width(p);
}

void	print_d_intmin(t_ftprint *p)
{
	int		precision_copy;

	precision_copy = p->field_precision;
	p->nb_neg = 1;
	p->nb_len = 10;
	p->arg_len = p->nb_len + 1;
	if (p->field_width > 0
		&& p->flag_precision && p->field_precision > p->nb_len)
		p->field_width--;
	print_d_handle_flags(p);
	ft_putstr_fd(p->fd, "2147483648");
	if (p->flag_precision && precision_copy > p->nb_len)
		p->count += p->arg_len + 1;
	else
		p->count += p->arg_len;
	if (p->flag_minus)
		ft_print_field_width(p);
}

void	print_d_zeroprec_zero(t_ftprint *p)
{
	p->nb_len = 0;
	p->arg_len = p->nb_len;
	if (!p->flag_minus)
		ft_print_field_width(p);
	if (!p->field_width)
		p->field_precision++;
	p->count += 0;
	if (p->flag_minus)
		ft_print_field_width(p);
}

void	print_d_default(t_ftprint *p, int nb)
{
	char	*str;

	ft_get_nb_len(p, nb, 10);
	str = ft_nb_str(nb, p);
	p->arg_len = p->nb_len;
	print_d_handle_flags(p);
	ft_putstr_fd(p->fd, str);
	free(str);
	p->count += p->arg_len;
	if (p->flag_minus)
		ft_print_field_width(p);
}
