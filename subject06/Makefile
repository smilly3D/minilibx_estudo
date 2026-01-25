NAME := subject06
CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3 -I../minilibx-linux

SRC := subject06.c
OBJ := $(SRC:.c=.o)

LDFLAGS := -L../minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

all: mlx $(NAME)

mlx:
	$(MAKE) -C ../minilibx-linux

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -f output.ppm

re: fclean all

.PHONY: all mlx clean fclean re
