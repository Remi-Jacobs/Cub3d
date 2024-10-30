NAME = libftprintf.a

LIBFT = ./libft

SRCS = 	ft_decimals_fmt.c \
		ft_hexas_fmt.c \
		ft_pointer_fmt.c \
		ft_printf.c \
		ft_string_fmt.c

OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wextra -Werror -Wall
RM = rm -f
INCLUDES = ft_printf.h

$(NAME): $(OBJS) $(INCLUDES)
	make -C $(LIBFT)
	cp ./libft/libft.a .
	mv libft.a $(NAME)
	ar rcs $(NAME) $(OBJS)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT)
re: fclean all
	make re -C $(LIBFT)

.PHONY: all clean fclean re

