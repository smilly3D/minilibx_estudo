NAME = fractal
SRCS = main.c
OBJS = $(SRCS:.c=.o)

UNAME := $(shell uname)

# MiniLibX path and library
# (manual override)
# MLX_PATH = ../minilibx_opengl_20191021
# MLX_PATH = ../minilibx-linux

ifeq ($(UNAME),Darwin)
	MLX_PATH = ../minilibx_opengl_20191021
	MLX_LINK = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit
else
	MLX_PATH = ../minilibx-linux
	MLX_LINK = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm -lbsd
endif

MLX_LIB = $(MLX_PATH)/libmlx.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_PATH) -O3

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(OBJS) $(MLX_LINK) -o $(NAME)

$(MLX_LIB):
	make -C $(MLX_PATH)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)

re: fclean all
