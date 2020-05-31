NAME = minishell
HEADER = incs/builtin.h incs/env.h incs/error.h incs/minishell.h 
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = src/utils/arg.c src/utils/error.c src/utils/free.c src/utils/prints.c\
		src/utils/reads.c src/builtins/builtins_nametab.c src/builtins/cd.c\
		src/builtins/echo.c src/builtins/env.c src/builtins/error.c\
		src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c\
		src/builtins/unset.c src/minishell.c
OBJ = $(SRC:.c=.o)
LIBFT = "src/"

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@(cd $(LIBFT)) && $(MAKE)
	@(mv libft.a .)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re