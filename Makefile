NAME = codexion

CC = cc

CFLAGS = -Wall -Werror -Wextra -g

HEADER = codexion.h

SRCS = codexion.c ft_atoi.c input_validator.c parsing.c coder_actions.c

all: $(NAME)

$(NAME): $(HEADER)
	$(CC) $(CFLAGS) $(SRCS) -o $@

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all
