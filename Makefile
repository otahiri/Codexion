NAME = codexion


CC = cc


CFLAGS = -Wall -Werror -Wextra -g


all = $(NAME)


SRCS = main.c parsing.c


OBJ = $(SRCS:.c=.o)


HEADER = codexion.h


%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)


$(NAME): $(HEADER) $(OBJ)
	$(CC) $(OBJ) -o $@


clean:
	rm -rf $(OBJ)


fclean: clean
	rm -rf $(NAME)


re: fclean $(NAME)
	

.PHONY: all clean fclean re
