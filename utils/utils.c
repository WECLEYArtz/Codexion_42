/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:21:31 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 16:44:54 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

t_timespec	get_abstime(t_timespec *last_compile, t_time_add *timeadd)
{
	struct timespec	abstime;

	abstime.tv_sec = last_compile->tv_sec + timeadd->sec;
	abstime.tv_nsec = last_compile->tv_nsec + timeadd->nsec;
	abstime.tv_sec += abstime.tv_nsec / 1000000000;
	abstime.tv_nsec = abstime.tv_nsec % 1000000000;
	return (abstime);
}

void	announce(t_coder *coder, short action, bool force)
{
	t_timespec				current;
	long					diff_ms;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static char				*str = "is debuging\0is refactoring\0burned out\0";

	if (sim_action(STAT, NULL) == END && force == false)
		return ;
	pthread_mutex_lock(&print_mutex);
	{
		clock_gettime(CLOCK_REALTIME, &current);
		diff_ms = ((current.tv_sec - coder->sim->startup.tv_sec) * 1000)
			+ ((current.tv_nsec - coder->sim->startup.tv_nsec) / 1000000);
		if (action == ANNOUCE_COMPILE)
		{
			printf("%ld %d has taken a dongle\n", diff_ms, coder->id);
			printf("%ld %d is compiling\n", diff_ms, coder->id);
		}
		else
			printf("%ld %d %s\n", diff_ms, coder->id, &str[action]);
	}
	pthread_mutex_unlock(&print_mutex);
}
