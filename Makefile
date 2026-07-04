CFLAGS=		-pthread -Wall -Werror -Wextra

NAME=		codexion

DEBUG=\
	  -g3\
	  -fsanitize=address\
	  # -fsanitize=leak

SRC=		main.c\
			cleaner.c\
			coder/coders.c coder/routines.c\
			dongle/dongle.c\
			parser/atopi.c parser/args_parser.c\
			simulation/simulation.c simulation/monitor.c\
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


test:
	echo "Renning test.sh..."
	bash test.sh


.PHONY: fclean all clean re Libft
