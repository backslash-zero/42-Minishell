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
				builtins/export_next.c 				\
				builtins/pwd.c 					\
				builtins/unset.c				\
				parsing/parsing.c				\
				parsing/parsing_clean.c			\
				parsing/parsing_clean_2.c		\
				parsing/parsing_substring.c		\
				parsing/parsing_utils.c			\
				parsing/parsing_utils_2.c		\
				parsing/parsing_utils_3.c		\
				parsing/parsing_variable.c		\
				utils/arg.c 					\
				utils/error.c 					\
				utils/free.c 					\
				utils/ft_strncpy.c 				\
				utils/pipe.c 					\
				utils/prints.c 					\
				utils/reads.c					\
				utils/redirections.c			\
				utils/semicolon.c				\
				utils/path.c					\
				minishell.c 					\


SRC			=	$(addprefix $(SRC_PATH), $(SRC_NAME))

OBJ			=	$(SRC:.c=.o)

LIBFT		=	src/libft/

PRINTF		=	src/ft_printf_fd/

LIBFTEXEC	=	src/libft/libft.a

PRINTFEXEC	=	src/ft_printf_fd/libftprintf.a 

MOV			=	"."

all: 		$(NAME)

$(NAME):	$(OBJ)
			@cd $(LIBFT) && $(MAKE) && $(MAKE) bonus
			@mv $(LIBFTEXEC) $(MOV)
			@cd $(PRINTF) && $(MAKE)
			@mv $(PRINTFEXEC) $(MOV)
			@$(CC) $(FLAGS) $(LEAKS) $(OBJ) -I$(HEADER) libft.a libftprintf.a -o $(NAME)
			@echo $(NAME) created

clean:
			@/bin/rm -f  $(OBJ)
			@(cd $(LIBFT) && $(MAKE) clean)
			@(cd $(PRINTF) && $(MAKE) clean)
			@/bin/rm -f libft.a libftprintf.a
			@echo Objects and libraries cleaned

fclean: 	clean
			@/bin/rm -f $(NAME)
			@echo $(NAME) deleted

re: 		fclean all

.PHONY:		all clean fclean re