NAME = so_long
PRINTF = ft_printf/libftprintf.a
MINILIBX = minilibx-linux/libmlx.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/get_next_line.c src/get_map.c src/main.c
OBJS = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(PRINTF) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PRINTF) $(MINILIBX)

$(PRINTF): empty
	make -C ft_printf
$(MINILIBX): empty
	make -C minilibx-linux
empty:

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean:
	rm -f $(OBJS)
	make clean -C ft_printf
	make clean -C minilibx-linux
fclean: clean
	rm -f $(NAME)
	rm -f $(MINILIBX)
	make fclean -C ft_printf
re: fclean all
# test: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c &&./a.out
# t: $(NAME)
# 	$(CC) $(CFLAGS) $(NAME) main.c
# test-: $(NAME)
# 	$(CC) $(NAME) main.c &&./a.out

.PHONY: all clean fclean re 