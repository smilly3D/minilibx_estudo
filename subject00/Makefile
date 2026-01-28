NAME := subject00
CC := cc
CFLAGS := -Wall -Wextra -Werror -O3 -DGL_SILENCE_DEPRECATION -I.. -I../minilibx_opengl_20191021

SRC := subject00.c
OBJ := $(SRC:.c=.o)

DEPS := ../subject.h

LDFLAGS := -L../minilibx_opengl_20191021 -lmlx -framework OpenGL -framework AppKit

all: mlx $(NAME)

mlx:
	$(MAKE) -C ../minilibx_opengl_20191021

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all mlx clean fclean re
