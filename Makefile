NAME = push_swap
BONUS = checker
CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = src/ps1.c libft/ft_split.c

OBJ = $(SRC:.c=.o)

SRC_BNS = gnl/get_next_line.c gnl/get_next_line_utils.c bonus/main.c libft/ft_split.c

OBJ_BNS = $(SRC_BNS:.c=.o)

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ)
	$(CC) $^ -o $@

$(BONUS): $(OBJ_BNS)
	$(CC)  $^ -o $@

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
