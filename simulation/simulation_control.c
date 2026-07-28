/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 13:20:47 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/28 21:16:21 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./simulation.h"

void __debug_sleep__(t_timespec *abstime)
{
	t_timespec now;
	clock_gettime(CLOCK_REALTIME, &now);

	printf("sleeping until:		%ld | %ld\nnow is:			%ld | %ld\n",
			abstime->tv_sec, abstime->tv_nsec, now.tv_sec, now.tv_nsec);
}

static void	_action_wait(pthread_cond_t *run_call, pthread_mutex_t *run_mutex,
		t_timespec *abstime, short *is_running)
{
	while (1)
	{
		// __debug_sleep__(abstime);
		if (pthread_cond_timedwait(run_call, run_mutex, abstime) || *is_running == END)
			return ;
	}
}

// NOTE: try to make every option returning the latest state
// 			this might need putting each one in an isolated function
short	sim_action(short choice, t_timespec *abstime)
{
	static pthread_mutex_t	run_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	run_call = PTHREAD_COND_INITIALIZER;
	static short			status = OFF;
	short					tmp;

	pthread_mutex_lock(&run_mutex);
	if (choice != STAT)
	{
		if (choice == WAIT_STP)
			_action_wait(&run_call, &run_mutex, abstime, &status);
		else if (choice == WAIT_RUN)
			while (status == OFF)
				pthread_cond_wait(&run_call, &run_mutex);
		else if (choice == END || choice == ON)
		{
			if(choice == ON)
				clock_gettime(CLOCK_REALTIME, abstime);
			status = choice;
			pthread_cond_broadcast(&run_call);
		}
	}
	tmp = status;
	return (pthread_mutex_unlock(&run_mutex), tmp);
}
