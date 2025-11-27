NAME = cub3d
SOURCE = $(shell find ./src -iname "*.c")

LIBMLX	= ./include/lib/MLX42
OBJS = $(SOURCE:.c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
INCLUDE = -I ./include -I $(LIBMLX)/include


all: libmlx $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(LIBS) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

libmlx: $(LIBMLX)
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -s -C $(LIBMLX)/build -j4

$(LIBMLX):
	@git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)

%.o: %.c
	@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

clean:
	@$(RM) $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf ./include/lib/.git
	@rm -rf $(LIBMLX)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx