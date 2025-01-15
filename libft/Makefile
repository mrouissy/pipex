NAME = libft.a

C = cc

FLAG = -Wall -Wextra -Werror

RM = rm -f

SRC = ft_strlen.c ft_putstr_fd.c

OBJ = $(SRC:.c=.o)


all: $(NAME)

$(NAME) : $(OBJ)
	ar rsc $(NAME) $(OBJ)

%.o: %.c
	$(C) $(FLAG) -c $< -o $@

clean:
	$(RM)  $(OBJ) $(OBONUS)

fclean : clean
	$(RM) $(NAME)

re : clean all


.PHONY: all, bonus, clean, fclean, re
