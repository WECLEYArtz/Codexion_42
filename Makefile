CFLAGS= -pthread -Wall -Werror -Wextra

NAME=codexion

DEBUG= -g -fsanitize=address -fsanitize=leak -fsanitize=thread 

SRC= main.c\
coder/coders.c coder/routines.c\
donle/dongle.c monitor/monitor.c\
parser/atopi.c parser/params_parser.c\
schedualer/schedualer.c\
simulation/simulation.h

OBJ=(SRC:%.o:%.c)

HEADER=codexion.h

all: $(NAME)
	$(CC) 

%.o:%.c dependencies.h

clean:
	rm -f $(OBJ)
	make fclean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean all clean re Libft
