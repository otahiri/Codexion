NAME = codexion

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g 
# -fsanitize=thread

HEADER = codexion.h

SRCS = actions.c coder_actions.c codexion.c dongle_actions.c \
       ft_atoi.c extra_utils.c min_heap_actions.c min_heap_utils.c parsing.c burn_out_monitor.c\
       switch_utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME) clean

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(HEADER) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
