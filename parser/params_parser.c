#include "../dependencies.h"
#include "../parser/parser.h"

t_params getparams(char **argv){
	t_params params;

	if (!strcmp(argv[8], "edf") || !strcmp(argv[8], "fifo")) 
		exit(puts("DEBUG: Invalid scheduler"));

	params.time_to_debug = ft_atopi(argv[1]);
	params.time_to_burnout = ft_atopi(argv[2]);
	params.time_to_compile = ft_atopi(argv[3]);
	params.time_to_debug = ft_atopi(argv[4]);
	params.time_to_refactor = ft_atopi(argv[5]);
	params.number_of_coders = ft_atopi(argv[6]);
	params.dongle_cooldown = ft_atopi(argv[7]);
	params.scheduler = ft_atopi(argv[8]);

	printf("\
	time_to_debug : %d \n\
	time_to_burnout : %d \n\
	time_to_compile : %d \n\
	time_to_debug : %d \n\
	time_to_refactor : %d \n\
	number_of_coders : %d \n\
	dongle_cooldown : %d \n\
	scheduler : %d \n",\

	params.time_to_debug,
	params.time_to_burnout,
	params.time_to_compile,
	params.time_to_debug,
	params.time_to_refactor,
	params.number_of_coders,
	params.dongle_cooldown,
	params.scheduler);

	return params;
}
