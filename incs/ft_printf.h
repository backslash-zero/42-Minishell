/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzafari <rzafari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 17:05:20 by cmeunier          #+#    #+#             */
/*   Updated: 2020/09/07 16:56:15 by rzafari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_ftprint
{
	va_list		list;
	int			fd;
	int			i;
	int			count;
	char		*str;
	int			flag_zero;
	int			flag_minus;
	int			flag_plus;
	int			flag_star;
	int			flag_precision;
	int			field_width;
	int			field_precision;
	int			arg_len;
	int			nb_len;
	int			nb_neg;
}				t_ftprint;

int				ft_printf_fd(int fd, const char *format, ...);
size_t			ft_strlen(const char *s);
void			ft_putchar_fd(int fd, char c);
void			ft_putstr_fd(int fd, char *s);
char			*ft_substr(char const *s, unsigned int start, int len);
void			print_s(t_ftprint *p);
void			print_c(t_ftprint *p);
void			print_p(t_ftprint *p);
void			print_d(t_ftprint *p);
void			print_d_precision(t_ftprint *p);
void			print_d_intmin(t_ftprint *p);
void			print_d_negative(t_ftprint *p, int nb);
void			print_d_handle_flags(t_ftprint *p);
void			print_d_default(t_ftprint *p, int nb);
void			print_d_zeroprec_zero(t_ftprint *p);
void			print_u(t_ftprint *p);
void			print_x_low(t_ftprint *p);
void			print_x_up(t_ftprint *p);
void			ft_getprecision(t_ftprint *p);
void			ft_precision_default(t_ftprint *p);
void			ft_print_precision(t_ftprint *p);
int				ft_putnbr_hex_len(t_ftprint *p, size_t nb, char *base);
int				ft_u_putnbr_len(t_ftprint *p, unsigned int nb);
int				ft_is_special(t_ftprint *p);
void			ft_size_flagstar(t_ftprint *p);
void			ft_size_default(t_ftprint *p);
void			ft_test_flags(t_ftprint *p);
void			ft_test_zero(t_ftprint *p);
void			ft_test_minus(t_ftprint *p);
void			ft_test_plus(t_ftprint *p);
void			ft_test_star(t_ftprint *p);
void			ft_test_precision(t_ftprint *p);
void			ft_print_precision(t_ftprint *p);
void			ft_test_size(t_ftprint *p);
void			ft_print_field_width(t_ftprint *p);
void			ft_tests_checks(t_ftprint *p);
void			ft_reset_struct(t_ftprint *p);
char			*ft_nb_str(int nb, t_ftprint *p);
void			ft_get_nb_len(t_ftprint *p, int nb, int base_len);
void			ft_get_nb_len_u(t_ftprint *p, unsigned int nb, int base_len);
char			*ft_nb_str_u(unsigned int nb, t_ftprint *p, int b_l, char *b);
char			*ft_nb_str(int nb, t_ftprint *p);
void			ft_printstring(t_ftprint *p, char *str);
void			print_d_zeroprec_zero(t_ftprint *p);

#endif
