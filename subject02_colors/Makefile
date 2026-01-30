NAME = fractal
SRCS = main.c
OBJS = $(SRCS:.c=.o)

# MiniLibX path and library
MLX_PATH = ../minilibx_opengl_20191021
MLX_LIB = $(MLX_PATH)/libmlx.a

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_PATH) -O3

# Frameworks for macOS
FRAMEWORKS = -framework OpenGL -framework AppKit
# Math library
LIBS = -lm

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(OBJS) -L$(MLX_PATH) -lmlx $(FRAMEWORKS) $(LIBS) -o $(NAME)

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
