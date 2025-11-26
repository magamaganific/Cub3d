NAME = Hello
CC=	 cc -Wall -Werror -Wextra -g3

MLX_PATH = minilibx-linux
SRC = main.c
OBJ = $(SRC:.c=.o)

MLX = $(MLX_PATH)/libmlx.a

all: $(NAME)

$(NAME): $(MLX) $(OBJ)
	$(CC) -lm -o $@ $^ -L$(MLX_PATH) -lmlx -lXext -lX11

%.o: %.c
	$(CC) -I$(MLX_PATH) -c -o $@ $<

$(MLX):
	@make -C $(MLX_PATH)

clean:
	@make -C $(MLX_PATH) clean
	rm -r $(OBJ)

fclean: clean
	@make -C $(MLX_PATH) clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
