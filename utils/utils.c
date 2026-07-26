/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:21:31 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/25 19:20:04 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
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

void	announce(t_coder *coder, short action, bool force)
{
	t_timespec				current;
	long					diff_ms;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static char				*str = "is debuging\0is refactoring\0burned out\0";

	pthread_mutex_lock(&print_mutex);
	if (sim_action(STAT, NULL) == ON || force == true)
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

//debug
#include "../dongle/dongle.h"
void __debug_heap__(t_dongle *dongle, t_coder *coder, char *msg)
{
	if (!HEAP_DEBUG)
		return;
	static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_lock(&mutex);

	printf("[ %d ]: heap [ %d - %d ] taken:(%d)\t\t[ %s ]\n",
			coder->id,
			dongle->heap[0]? dongle->heap[0]->id: 0,
			dongle->heap[1]? dongle->heap[1]->id: 0,
			dongle->taken,
			msg);
	pthread_mutex_unlock(&mutex);
};
//debug
