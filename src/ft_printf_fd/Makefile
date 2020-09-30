# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cmeunier <cmeunier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/12/06 14:57:55 by cmeunier          #+#    #+#              #
#    Updated: 2020/06/10 23:59:33 by cmeunier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	clang

CFLAGS	+=	-Wall -Wextra -Werror

SRC 	=		ft_printf_fd.c						\
				ft_field_width.c				\
				ft_precision.c					\
				ft_type_print_char.c			\
				ft_type_print_d.c				\
				ft_type_print_other.c			\
				ft_num_conversion.c				\
				ft_test_flags.c					\
				ft_utils.c						\
				ft_putchar.c					\
				ft_strlen.c						\
				ft_putstr.c						\
				ft_substr.c						\

OBJ		=	$(SRC:%.c=%.o)

NAME	=	libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	@echo "libftprintf.a ready"

%.o:	%.c
		@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJ)

fclean:
	$(MAKE) clean
	@rm -f $(NAME)
	@rm -f *~

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus