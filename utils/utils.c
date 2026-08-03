/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:21:31 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/03 01:38:03 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"

t_timespec	get_abstime(t_timespec *time, t_time_add *addition)
{
	struct timespec	new_abstime;

	new_abstime.tv_sec = time->tv_sec + addition->sec;
	new_abstime.tv_nsec = time->tv_nsec + addition->nsec;
	new_abstime.tv_sec += new_abstime.tv_nsec / 1000000000;
	new_abstime.tv_nsec = new_abstime.tv_nsec % 1000000000;
	return (new_abstime);
}

void	announce(t_coder *coder, short action)
{
	t_timespec				current;
	long					diff;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static bool				print_allowed = true;
	static char				*msgs[3] = {
		"is debuging", "is refactoring", RED"burned out"RESET
	};

	clock_gettime(CLOCK_REALTIME, &current);
	diff = ((current.tv_sec - coder->sim->startup.tv_sec) * 1000)
		+ ((current.tv_nsec - coder->sim->startup.tv_nsec) / 1000000);
	pthread_mutex_lock(&print_mutex);
	if (print_allowed)
	{
		if (action == ANNOUCE_COMPILE)
			printf("%ld %d %s\n%ld %d %s\n%ld %d %s\n",
				diff, coder->id, "has taken a dongle",
				diff, coder->id, "has taken a dongle",
				diff, coder->id, GREEN"is compiling"RESET);
		else
			printf("%ld %d %s\n", diff, coder->id, msgs[action]);
	}
	if (action == ANNOUCE_BURNOUT)
		print_allowed = false;
	pthread_mutex_unlock(&print_mutex);
}

void	single_announce(t_coder *coder)
{
	t_timespec	current;
	long		diff;

	clock_gettime(CLOCK_REALTIME, &current);
	diff = ((current.tv_sec - coder->sim->startup.tv_sec) * 1000)
		+ ((current.tv_nsec - coder->sim->startup.tv_nsec) / 1000000);
	printf("%ld %d %s\n", diff, coder->id, "has taken a dongle");
}
