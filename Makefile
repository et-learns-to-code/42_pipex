NAME = pipex
NAME_B = pipex_bonus

SRCS = srcs/pipex.c srcs/utils.c
OBJS = ${SRCS:.c=.o}

SRCS_B = srcs/pipex_bonus.c srcs/utils_bonus.c
OBJS_B = ${SRCS_B:.c=.o}

HEADER = -Iincludes

LIBFT_DIR = libft/

CC = gcc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make re -C $(LIBFT_DIR)
	$(CC) $(OBJS) -Llibft -lft -o $(NAME)

bonus: $(NAME_B)

$(NAME_B): $(OBJS_B)
	make re -C $(LIBFT_DIR)
	$(CC) $(OBJS_B) -Llibft -lft -o $(NAME_B)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME) $(NAME_B)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus
