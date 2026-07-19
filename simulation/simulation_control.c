/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 13:20:47 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 16:44:36 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./simulation.h"

static void	_routine_wait(pthread_cond_t *cond, pthread_mutex_t *mutex,
		t_timespec *abstime, short *is_running)
{
	while (1)
		if (pthread_cond_timedwait(cond, mutex, abstime) || *is_running == END)
			return ;
}

short	sim_action(short choice, t_timespec *abstime)
{
	static pthread_mutex_t	run_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	run_call = PTHREAD_COND_INITIALIZER;
	static short			status = OFF;
	short					tmp;

	pthread_mutex_lock(&run_mutex);
	tmp = status;
	if (choice != STAT)
	{
		if (choice == WAIT_STP)
			_routine_wait(&run_call, &run_mutex, abstime, &status);
		else if (choice == WAIT_RUN)
		{
			while (status == OFF)
				pthread_cond_wait(&run_call, &run_mutex);
			tmp = status;
		}
		else if (choice == END || choice == ON)
		{
			status = choice;
			pthread_cond_broadcast(&run_call);
		}
	}
	return (pthread_mutex_unlock(&run_mutex), tmp);
}
