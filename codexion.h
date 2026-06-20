#ifndef CODEXION_H
#define CODEXION_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


// The structure to 
typedef struct s_prgrm_args {
	int number_of_coders;
	int time_to_burnout;
	int time_to_compile;
	int time_to_debug;
	int time_to_refactor;
	int number_of_compiles_required;
	int dongle_cooldown;
	int scheduler;
} t_prgrm_args;

#endif 
