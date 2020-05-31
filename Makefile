NAME = minishell
HEADER = "/incs/builtin.h" "/incs/env.h" "/incs/error.h" "/incs/minishell.h"
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = src/builtins/builtins_nametab.c src/builtins/cd.c src/builtins/echo.c src/builtins/env.c\
	src/builtins/exit.c src/builtins/export.c src/builtins/pwd.c src/builtins/unset.c\
	src/utils/arg.c src/utils/error.c src/utils/free.c src/utils/prints.c src/utils/reads.c
OBJ= $(SRC:.c=.o)
LIBFT = "src/libft"
all: $(NAME)

$(NAME): $(OBJ)
	@(cd $(LIBFT) && $(MAKE))
	$(CC) $(FLAGS) $(OBJ) -I$(HEADER) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re