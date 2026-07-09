CFLAGS=		-pthread -Wall -Werror -Wextra

NAME=		codexion

DEBUG=\
	  -g3\
	  # -fsanitize=address\
	  # -fsanitize=leak
	  # -fsanitize=thread

SRC=		main.c\
			cleaner.c\
			coder/coders.c coder/routines.c \
			dongle/dongle.c \
			monitor/monitor.c monitor/burnoutpq_control.c \
			parser/args_parser.c parser/atopi.c \
			schedualer/schedualer.c \
			simulation/simulation_control.c simulation/simulation_init.c \

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
