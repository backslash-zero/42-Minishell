# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzafari <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 14:43:22 by rzafari           #+#    #+#              #
#    Updated: 2019/10/24 10:10:57 by rzafari          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a
HEADER= "/incs/libft.h"
CC=gcc
FLAGS= -Wall -Wextra -Werror
SRC= ft_atoi.c ft_is_space.c ft_isprint.c ft_memcpy.c ft_split.c ft_strmapi.c ft_toupper.c\
	ft_bzero.c ft_itoa.c ft_memmove.c ft_strchr.c ft_strncmp.c ft_calloc.c\
	ft_memset.c ft_strdup.c ft_strldup.c ft_strnstr.c ft_isalnum.c ft_putchar_fd.c ft_putchar.c\
    ft_strjoin.c ft_strrchr.c ft_isalpha.c ft_memccpy.c ft_putendl_fd.c\
	ft_strlcat.c ft_strtrim.c ft_strtrim_char.c ft_isascii.c ft_memchr.c ft_putnbr_fd.c\
	ft_strlcpy.c ft_substr.c ft_isdigit.c ft_memcmp.c ft_putstr_fd.c ft_putstr.c\
	ft_strlen.c ft_tolower.c ft_strcmp.c ft_split2.c
OBJ= $(SRC:.c=.o)
B_SRC=ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c\
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
B_OBJ= $(B_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -I$(HEADER) -c $(SRC)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo $(NAME) ready	

bonus: $(B_OBJ)
	@$(CC) $(FLAGS) -I$(HEADER) -c $(B_SRC)
	@ar rc $(NAME) $(B_OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -f $(OBJ) $(B_OBJ)
fclean: clean
	@/bin/rm -f $(NAME)
re: fclean all bonus