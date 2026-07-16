/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:21:31 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/16 12:48:24 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder/coder.h"
#include "dependencies.h"
#include "simulation/simulation.h"

t_timespec	get_abstime(t_timespec *last_compile, t_timeadd *timeadd)
{
	struct timespec	abstime;

	abstime.tv_sec = last_compile->tv_sec + timeadd->sec;
	abstime.tv_nsec = last_compile->tv_nsec + timeadd->nsec;
	abstime.tv_sec += abstime.tv_nsec / 1000000000;
	abstime.tv_nsec = abstime.tv_nsec % 1000000000;
	return (abstime);
}

void	announce(t_coder *coder, char *action, int force)
{
	t_timespec				current;
	long					timelap;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&print_mutex);
	if (sim_action(STAT, NULL) || force)
	{
		clock_gettime(CLOCK_REALTIME, &current);
		timelap = (current.tv_sec * 1000 + current.tv_nsec / 1000000)
			- (coder->sim->startup.tv_sec * 1000 + coder->sim->startup.tv_nsec
				/ 1000000);
		printf("%ld %d %s\n", timelap, coder->id, action);
	}
	pthread_mutex_unlock(&print_mutex);
}
