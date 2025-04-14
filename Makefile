NAME = fractol
LIBFT = ./libft/libft.a
MLX = ./minilibx-linux/libmlx_Linux.a

SOURCES = ./src/fractol.c ./src/utils.c ./src/events.c ./src/render.c \
		  ./src/complex_utils.c
OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS_GENERAL = -Wall -Wextra -Werror
CFLAGS_LIBS = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

all: $(LIBFT) $(MLX) $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^ $(LIBFT) $(MLX) $(CFLAGS_GENERAL) $(CFLAGS_LIBS)

./src/%.o: ./src/%.c
	$(CC) -c $^ $(CFLAGS_GENERAL)
	mv *.o src

$(LIBFT):
	make -C ./libft

$(MLX):
	make -C ./minilibx-linux

clean:
	rm -f $(OBJECTS)
	make -C ./libft clean
fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
	make -C ./minilibx-linux clean

re: fclean all

.PHONY: all mlx clean fclean re
