CFLAGS=		-pthread -Wall -Werror -Wextra

NAME=		codexion

DEBUG=\
	  # -g\
	  # -fsanitize=address\
	  # -fsanitize=leak

SRC=		main.c\
			coder/coders.c coder/routines.c\
			dongle/dongle.c monitor/monitor.c\
			parser/atopi.c parser/params_parser.c\
			schedualer/schedualer.c\

OBJ=		$(SRC:.c=.o)

HEADER=		codexion.h

all:		$(NAME)

$(NAME): 	$(OBJ) 
	$(CC) $(CFLAGS) $(DEBUG) -o $(NAME) $(OBJ)

%.o:%.c		dependencies.h
	$(CC) -c $(CFLAGS) $(DEBUG) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re Libft
