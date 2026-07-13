/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 13:20:47 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/13 20:17:13 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./simulation.h"

static bool	_simulation_runtime_handler(short choice)
{
	static pthread_mutex_t	running_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	run_call = PTHREAD_COND_INITIALIZER;
	static bool				is_running = false;
	bool					_is_running;

	pthread_mutex_lock(&running_mutex);
	_is_running = is_running;
	if (choice == STOP)
		is_running = false;
	else if (choice == HOLD)
		while (is_running == false)
			pthread_cond_wait(&run_call, &running_mutex);
	else if (choice == STAT)
		return (pthread_mutex_unlock(&running_mutex), _is_running);
	else if (choice == TOGGLE)
	{
		pthread_cond_broadcast(&run_call);
		is_running = !_is_running;
	}
	pthread_mutex_unlock(&running_mutex);
	return (0);
}

void	sim_lauch_toggle(void)
{
	_simulation_runtime_handler(TOGGLE);
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
