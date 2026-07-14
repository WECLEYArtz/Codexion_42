#include "dependencies.h"

struct timespec	 get_abstime(t_timeval *last_compile, t_timeadd *timeadd)
{
	struct timespec	abstime;

	abstime.tv_sec = last_compile->tv_sec + timeadd->sec;
	abstime.tv_nsec = (last_compile->tv_usec + timeadd->usec) * 1000;
	abstime.tv_sec += abstime.tv_nsec / 1000000000;
	abstime.tv_nsec = abstime.tv_nsec % 1000000000;
	return (abstime);
}
