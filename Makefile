NAME		=	minishell

HEADER		=	incs/

CC			=	gcc

FLAGS		=	-Wall -Wextra -Werror

LEAKS		=	-g3 -fsanitize=address

SRC_PATH	=	src/

SRC_NAME	=	builtins/builtins_nametab.c 				\
				builtins/cd.c 								\
				builtins/echo.c 							\
				builtins/env.c								\
				builtins/exit.c 							\
				builtins/export.c 							\
				builtins/export_2.c 						\
				builtins/export_next.c 						\
				builtins/export_next_2.c 					\
				builtins/pwd.c 								\
				builtins/unset.c							\
				parsing/parsing.c							\
				parsing/append.c							\
				parsing/cleanup/cleanup.c					\
				parsing/cleanup/cleanup_var.c				\
				parsing/cleanup/cleanup_gret.c				\
				parsing/cleanup/cleanup_bs_quote.c			\
				parsing/utils/is_funcs/is_funcs_1.c			\
				parsing/utils/is_funcs/is_funcs_2.c			\
				parsing/utils/is_funcs/is_funcs_3.c			\
				parsing/utils/tools/backslash_tools_1.c		\
				parsing/utils/tools/backslash_tools_2.c		\
				parsing/utils/tools/gret_tools.c			\
				parsing/utils/tools/quote_tools.c			\
				parsing/utils/tools/var_tools_1.c			\
				parsing/utils/tools/var_tools_2.c			\
				parsing/utils/tools/redir_pipe_tools.c		\
				parsing/utils/tools/semicolon_tools.c		\
				parsing/utils/parsing_utils_1.c				\
				pipe/pipe.c									\
				pipe/pipe2.c								\
				pipe/pipe3.c								\
				utils/arg.c 								\
				utils/error.c 								\
				utils/free.c 								\
				utils/ft_strncpy.c 							\
				utils/prints.c 								\
				execs/reads.c								\
				execs/reads_2.c								\
				execs/redirections.c						\
				execs/redirections2.c						\
				utils/semicolon.c							\
				execs/path.c								\
				execs/path_2.c								\
				tools/tools.c								\
				minishell.c 								\

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