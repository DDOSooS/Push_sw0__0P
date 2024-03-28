NAME = push_swap

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = src/ps1.c libft/ft_split.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -fsanitize=address -g $^ -o $@

%.o: %.c
	$(CC)  -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re