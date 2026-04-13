NAME = codexion

CC = cc

CFLAGS = -Wall -Werror -Wextra -g
# -fsanitize=thread

HEADER = codexion.h

SRCS = actions.c burn_out_monitor.c coder_actions.c codexion.c dongle_actions.c extra_utils.c\
		ft_atoi.c min_heap_actions.c min_heap_utils.c parsing.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(HEADER) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
