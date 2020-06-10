NAME		=	minishell

HEADER		=	incs/

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

LEAKS		=	-g -fsanitize=address

SRC_PATH	=	src/

SRC_NAME	=	builtins/builtins_nametab.c 	\
				builtins/cd.c 					\
				builtins/echo.c 				\
				builtins/env.c					\
				builtins/exit.c 				\
				builtins/export.c 				\
				builtins/pwd.c 					\
				builtins/unset.c				\
				utils/arg.c 					\
				utils/error.c 					\
				utils/free.c 					\
				utils/prints.c 					\
				utils/reads.c					\
				minishell.c 					\

SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ			=	$(SRC:.c=.o)

LIBFT		=	src/libft/

LIBFTEXEC	=	src/libft/libft.a

MOV			=	"."

all: 		$(NAME)

$(NAME):	$(OBJ)
			cd $(LIBFT) && $(MAKE) && $(MAKE) bonus
			mv $(LIBFTEXEC) $(MOV)
			$(CC) $(FLAGS) $(LEAKS) $(OBJ) -I$(HEADER) libft.a -o $(NAME)

clean:
			@/bin/rm -f  $(OBJ)
			@(cd $(LIBFT) && $(MAKE) clean)
			@/bin/rm -f libft.a

fclean: 	clean
			/bin/rm -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re