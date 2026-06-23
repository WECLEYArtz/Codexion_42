#ifndef PARSER_H
#define PARSER_H

// The one time used structure for a shared prointer to all depending on it.
// preventing data duplication in runtime

typedef struct s_params {
	const int number_of_coders;
	const int time_to_burnout;
	const int time_to_compile;
	const int time_to_debug;
	const int time_to_refactor;
	const int number_of_compiles_required;
	const int dongle_cooldown;
	const int scheduler;
} t_params;

#endif
