#include "../dependencies.h"
#include "../parser/parser.h"

t_params* getparams(char **args){
	t_params* params = malloc(sizeof(t_params));

	if(!params)
		exit(puts("DEBUG: Failed allocation"));

	return params;
}
