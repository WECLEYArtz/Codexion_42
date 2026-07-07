/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 13:20:47 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/07 14:24:07 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "./launch_handler.h"

static bool	_simulation_runtime_handler(short choice)
{
	static pthread_mutex_t	running_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	run_call = PTHREAD_COND_INITIALIZER;
	static bool				is_running = false;

	pthread_mutex_lock(&running_mutex);
	if (choice == STOP)
		is_running = false;
	else if (choice == HOLD)
		while (is_running == false)
			pthread_cond_wait(&run_call, &running_mutex);
	else if (choice == STAT)
		return (pthread_mutex_unlock(&running_mutex), is_running);
	else if (choice == RUN)
	{
		pthread_cond_broadcast(&run_call);
		is_running = true;
	}
	pthread_mutex_unlock(&running_mutex);
	return (0);
}

void	sim_lauch_run(void)
{
	_simulation_runtime_handler(RUN);
}

void	sim_launch_hold(void)
{
	_simulation_runtime_handler(HOLD);
}

void	sim_stop(void)
{
	_simulation_runtime_handler(STOP);
}

bool	sim_running_status(void)
{
	return (_simulation_runtime_handler(STAT));
}
