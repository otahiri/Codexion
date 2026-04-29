NAME = codexion

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread

HEADER = coders/codexion.h

SRCS = coders/burn_monitor.c coders/coder_action.c coders/coders_utils.c coders/codexion.c\
	coders/dongle_actions.c coders/dongle_utils.c coders/ft_atoi.c coders/min_heap.c\
	coders/min_heap_utils.c coders/parsing.c coders/switch_utils.c coders/utils_one.c coders/utils_two.c\
	coders/utils_three.c

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
