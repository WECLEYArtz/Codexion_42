/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 13:20:47 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/17 11:00:47 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "./simulation.h"

static void	_routine_wait(pthread_cond_t *cond, pthread_mutex_t *mutex,
		t_timespec *abstime, bool *is_running)
{
	while (1)
		if (pthread_cond_timedwait(cond, mutex, abstime)
			|| *is_running == false)
			return ;
}

bool	sim_action(short choice, t_timespec *abstime)
{
	static pthread_mutex_t	run_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	run_call = PTHREAD_COND_INITIALIZER;
	static bool				is_running = false;
	bool					tmp;

	pthread_mutex_lock(&run_mutex);
	tmp = is_running;
	if (choice != STAT)
	{
		if (choice == WAITSTP)
			_routine_wait(&run_call, &run_mutex, abstime, &is_running);
		else if (choice == WAITRUN)
		{
			while (is_running == false)
				pthread_cond_wait(&run_call, &run_mutex);
			tmp = is_running;
		}
		else if (choice == OFF || choice == ON)
		{
			is_running = choice;
			pthread_cond_broadcast(&run_call);
		}
	}
	return (pthread_mutex_unlock(&run_mutex), tmp);
}
