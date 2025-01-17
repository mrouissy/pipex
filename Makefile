NAME = pipex

C = gcc

FLAG = -Werror -Wall -Wextra -fsanitize=address

RM = rm -f

SRC = src/pipex.c

LIBFT = libft/libft.a

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft
	@$(C) $(FLAG) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	@$(C) $(FLAG) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@make clean -C libft

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
