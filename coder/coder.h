#ifndef CODER_H
#define CODER_H

#include "../dependencies.h"
#include "../parser/parser.h"

typedef struct s_coder {
	int id;
	int compiled;
	pid_t thread;
	int last_compile;
	t_params* params;
} t_coder;


#endif
