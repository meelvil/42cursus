CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD

SOURCES = ft_printf.c

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

NAME = libftprintf.a

HEADER = -I .

all: $(NAME)

%.o: %.c Makefile
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $@ $^

.PHONY: all clean fclean re

clean:
	rm -f $(OBJECTS) $(DEPS)

fclean: cleam
	rm -f $(NAME)

-include $(DEPS)

re: fclean all