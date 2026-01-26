NAME := subject00
CC := gcc
CFLAGS := -Wall -Wextra -Werror -O3 -I.. -I../minilibx-linux

SRC := subject00.c
OBJ := $(SRC:.c=.o)

DEPS := ../subject.h

LDFLAGS := -L../minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

all: mlx $(NAME)

mlx:
	$(MAKE) -C ../minilibx-linux

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
