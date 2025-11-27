NAME = cub3d
SOURCE = $(shell find ./src -iname "*.c")

LIBMLX	= ./include/lib/MLX42
OBJS = $(SOURCE: .c=.o)
CC = cc
FLAGS = -Wall -Wextra -Werror
INCLUDE = -I ./include -I $(LIBMLX)/include

all: libmlx $(NAME)

$(NAME): $(OBJS)
	$(CC) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@ && printf "Compiling: $(notdir $<)\n"

clean:
	$(RM) $(OBJS)
	@rm -rf $(LIBMLX)/build

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re libmlx