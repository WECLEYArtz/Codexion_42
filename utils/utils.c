/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/16 00:21:31 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/05 17:33:27 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

t_timespec	get_abstime(t_timespec *time, t_time_add *addition)
{
	struct timespec	new_abstime;

	new_abstime.tv_sec = time->tv_sec + addition->sec;
	new_abstime.tv_nsec = time->tv_nsec + addition->nsec;
	new_abstime.tv_sec += new_abstime.tv_nsec / 1000000000;
	new_abstime.tv_nsec = new_abstime.tv_nsec % 1000000000;
	return (new_abstime);
}

static void	_announce_exec(short action, long diff, t_coder *coder)
{
	static char	*msgs[3] = {
		"is debuging", "is refactoring", RED "burned out" RESET};

	if (action == ANNOUCE_COMPILE)
		printf("%ld %d %s\n%ld %d %s\n%ld %d %s\n", diff, coder->id,
			"has taken a dongle", diff, coder->id, "has taken a dongle", diff,
			coder->id, GREEN "is compiling" RESET);
	else if (action == ANNOUCE_SINGLE)
		printf("%ld %d %s\n", diff, coder->id, "has taken a dongle");
	else
		printf("%ld %d %s\n", diff, coder->id, msgs[action]);
}

void	announce(t_coder *coder, short action)
{
	t_timespec				current;
	long					diff;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;
	static bool				print_allowed = true;

	clock_gettime(CLOCK_REALTIME, &current);
	diff = ((current.tv_sec - coder->sim->startup.tv_sec) * 1000)
		+ ((current.tv_nsec - coder->sim->startup.tv_nsec) / 1000000);
	pthread_mutex_lock(&print_mutex);
	if (print_allowed)
		_announce_exec(action, diff, coder);
	if (action == ANNOUCE_BURNOUT)
		print_allowed = false;
	pthread_mutex_unlock(&print_mutex);
}
