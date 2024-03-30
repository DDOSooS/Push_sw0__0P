NAME = push_swap
BONUS = checker
CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC = src/main.c libft/ft_atol.c libft/ft_strlen.c libft/ft_split.c src/parsing.c \
		src/parsing_utils.c src/parsing_utils1.c src/push_swap_cmd.c src/push_swap_cmd1.c src/push_swap_cmd2.c \
		src/sorting_algo.c src/sorting_algo_utils1.c src/sorting_algo_utils2.c \
		src/sorting_algo_utils3.c

OBJ = $(SRC:.c=.o)

SRC_BNS = gnl/get_next_line.c gnl/get_next_line_utils.c bonus/main_bonus.c \
			libft/ft_atol.c libft/ft_strlen.c libft/ft_split.c libft/ft_split.c libft/ft_strncmp.c libft/ft_strcmp.c  \
			bonus/parsing_bonus.c bonus/parsing_utils_bonus.c bonus/parsing_utils1_bonus.c \
			bonus/push_swap_cmd_bonus.c bonus/push_swap_cmd1_bonus.c bonus/push_swap_cmd2_bonus.c 

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
	$(RM) $(OBJ) $(OBJ_BNS)

fclean: clean
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
