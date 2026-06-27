#ifndef DEBUG_C
#define DEBUG_C

#include "simulation/simulation.h"

// a funciton only for debug perporses
void	db_announce(t_sim *sim, char *action)
{
	pthread_mutex_lock(&sim->print_mutex);
	printf("DEBUG: %s\n", action);
	pthread_mutex_unlock(&sim->print_mutex);
}

#endif
