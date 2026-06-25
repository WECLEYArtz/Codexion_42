#include "../dependencies.h"
#include "../parser/parser.h"

t_params getparams(char **argv){
	t_params params;

	if (!strcmp(argv[8], "edf"))
		params.scheduler = 1; 
	else if(!strcmp(argv[8], "fifo"))
		params.scheduler = 2; 
	else
		exit(puts("DEBUG: Invalid scheduler"));
	params.time_to_debug = ft_atopi(argv[1]);
	params.time_to_burnout = ft_atopi(argv[2]);
	params.time_to_compile = ft_atopi(argv[3]);
	params.time_to_debug = ft_atopi(argv[4]);
	params.time_to_refactor = ft_atopi(argv[5]);
	params.number_of_coders = ft_atopi(argv[6]);
	params.dongle_cooldown = ft_atopi(argv[7]);

	return params;
}
