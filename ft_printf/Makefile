CC = cc
CFLAGS = -Wall -Wextra -Werror -MMD

SOURCES = ft_printf.c ft_format.c ft_putchar.c\
	ft_putstr.c ft_putnbr.c ft_putunsignednbr.c ft_puthex.c\
	ft_printadress.c

OBJECTS = $(SOURCES:.c=.o)
DEPS = $(SOURCES:.c=.d)

NAME = libftprintf.a

HEADER = -I .

all: $(NAME)

%.o: %.c ft_printf.h Makefile
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(NAME): $(OBJECTS)
	ar rcs $@ $^

clean:
	rm -f $(OBJECTS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEPS)
