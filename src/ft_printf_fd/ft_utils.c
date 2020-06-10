/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 18:29:51 by cmeunier          #+#    #+#             */
/*   Updated: 2020/06/10 22:05:42 by cmeunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/ft_printf.h"

void	ft_reset_struct(t_ftprint *p)
{
	p->flag_zero = 0;
	p->field_width = 0;
	p->flag_precision = 0;
	p->arg_len = 0;
	p->nb_len = 0;
	p->flag_minus = 0;
	p->flag_plus = 0;
	p->flag_precision = 0;
	p->flag_star = 0;
	p->nb_neg = 0;
}

int		ft_is_special(t_ftprint *p)
{
	if (p->str[p->i] == '%' ||
		p->str[p->i] == '-' ||
		p->str[p->i] == '+' ||
		p->str[p->i] == '0' ||
		p->str[p->i] == '*' ||
		p->str[p->i] == '.' ||
		(p->str[p->i] >= '0' && p->str[p->i] <= '9'))
		return (1);
	else
		return (0);
}
