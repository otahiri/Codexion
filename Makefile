NAME = CODEXION

CC = cc

CFLAGS = -Wall -Werror -Wextra

HEADER = codexion.h

SRCS = codexion.c ft_atoi.c parsing.c

all: $(NAME)

$(NAME): $(HEADER)
	$(CC) $(CFLAGS) $(SRCS) -o $@


