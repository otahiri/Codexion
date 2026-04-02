NAME = CODEXION

CC = cc

CFLAGS = -Wall -Werror -Wextra

HEADER = codexion.h

SRCS = codexion.c

all: $(NAME)

$(NAME): $(HEADER)
	$(CC) $(CFLAGS) $(SRCS) -o $@


