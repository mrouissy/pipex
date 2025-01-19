NAME = libft.a

C = cc

FLAG = -Wall -Wextra -Werror

RM = rm -f

SRC =  ft_putstr_fd.c ft_strcmp.c ft_strlcpy.c ft_substr.c ft_calloc.c ft_split.c ft_strjoin.c ft_strlen.c ft_bzero.c
OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME) : $(OBJ)
	@ar rsc $(NAME) $(OBJ)

%.o: %.c
	@$(C) $(FLAG) -c $< -o $@

clean:
	@$(RM)  $(OBJ)

fclean : clean
	@$(RM) $(NAME)

re : clean all


.PHONY: all, bonus, clean, fclean, re
