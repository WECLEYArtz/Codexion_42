CFLAGS= -pthread -Wall -Werror -Wextra

DEBUG= -g -fsanitize=address -fsanitize=leak -fsanitize=thread 

SRC= 

OBJ=

HEADER=codexion.h

all: ()

%.o:%.c codexion.h
