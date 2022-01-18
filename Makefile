NAME = so_long
LIBFT = libft/libft.a
MINILIBX = minilibx-linux/libmlx.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = src/get_map.c src/main.c src/get_map_utils.c src/hook_functions.c \
		 src/get_image_utils.c
OBJS = $(SRCS:%.c=%.o)

FRAMEWORK = -L ./minilibx-linux -lmlx -I ./minilibx-linux -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(LIBFT) $(MINILIBX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FRAMEWORK)

$(LIBFT): empty
	make bonus -C libft
$(MINILIBX): empty
	make -C minilibx-linux

empty:

%.o:%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJS)
	make clean -C libft
	make clean -C minilibx-linux || :
fclean: clean
	rm -f $(NAME)
	rm -f $(MINILIBX) || :
	rm -f $(LIBFT)
re: fclean all

.PHONY: all clean fclean re