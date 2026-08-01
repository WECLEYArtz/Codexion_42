CFLAGS=		-pthread -Wall -Werror -Wextra
NAME=		codexion
DEPFLAGS=	-MMD

BUILD:=		.build
SRC= 		main.c cleaner.c \
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

OBJ=		$(addprefix $(BUILD)/,$(SRC:.c=.o))
DEP=		$(addprefix $(BUILD)/,$(SRC:.c=.d))

all:		$(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

$(BUILD)/%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(DEPFLAGS) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEP)

.PHONY: fclean all clean re
