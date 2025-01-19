NAME = pipex

C = gcc

FLAG = -Wall -Wextra -Werror

RM = rm -f

SRC =  src/pipex.c src/pipex_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME) :$(OBJ) 
	@make -C libft
	@$(C) $(FLAG) $(SRC) ./libft/libft.a -o $(NAME)

clean:
	@make clean -C libft
	@$(RM)  $(OBJ)  

fclean : clean
	@make fclean -C libft
	@$(RM) $(NAME)

re : fclean all


.PHONY: all, bonus, clean, fclean, re
