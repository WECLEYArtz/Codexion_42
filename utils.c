#include "dependencies.h"
#include "simulation/simulation.h"
#include "coder/coder.h"

struct timespec	 get_abstime(t_timeval *last_compile, t_timeadd *timeadd)
{
	struct timespec	abstime;

	abstime.tv_sec = last_compile->tv_sec + timeadd->sec;
	abstime.tv_nsec = (last_compile->tv_usec + timeadd->usec) * 1000;
	abstime.tv_sec += abstime.tv_nsec / 1000000000;
	abstime.tv_nsec = abstime.tv_nsec % 1000000000;
	return (abstime);
}


void	announce(t_coder *coder, char *action, int force)
{
	t_timeval				current;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	if(sim_get_status() || force)
	{
		gettimeofday(&current, NULL);
		pthread_mutex_lock(&print_mutex);
		printf("%ld %d %s\n", (current.tv_sec * 1000 + current.tv_usec / 1000)
				- (coder->sim->startup.tv_sec * 1000 + coder->sim->startup.tv_usec
					/ 1000), coder->id, action);
		pthread_mutex_unlock(&print_mutex);
	}
}
