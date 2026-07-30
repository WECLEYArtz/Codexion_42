CFLAGS=		-pthread -Wall -Werror -Wextra

NAME=		codexion

DEBUG=\
	  -g3 -Og\
	  # -fsanitize=thread \
	  # -fsanitize=leak \
	  # -fsanitize=address \

SRC=		main.c cleaner.c \
			utils/utils.c \
			parser/args_parser.c \
			parser/atopi.c \
			coder/coders.c \
			coder/routines.c \
			dongle/dongle_utils.c \
			dongle/heap_utils.c \
			monitor/monitor.c \
			monitor/burnout_wl_control.c \
			simulation/simulation_init.c \
			simulation/simulation_control.c \
			simulation/simulation_init_utils.c \
			simulation/simulation_preseeders.c \

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
