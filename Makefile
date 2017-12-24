CC = gcc
ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Werror -Wextra -g -O0 -fsanitize=address
else
	CFLAGS = -Ofast -march=native -Wall -Wextra
endif
NAME = test

.PHONY: clean fclean re

SRC = hashmap_init_crc_0.c hashmap_init_crc_1.c hashmap_init_crc_2.c hashmap_init.c \
	ft.c hashmap_crc32.c hashmap.c hashmap_op.c main.c
HEADERS = ft.h hashmap.h

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
