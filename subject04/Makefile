NAME := subject04
CC := cc
CFLAGS := -Wall -Wextra -Werror -O3 -DGL_SILENCE_DEPRECATION -I../minilibx_opengl_20191021

SRC := subject04.c
OBJ := $(SRC:.c=.o)

LDFLAGS := -L../minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

all: mlx $(NAME)

mlx:
	$(MAKE) -C ../minilibx_opengl_20191021

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all mlx clean fclean re
