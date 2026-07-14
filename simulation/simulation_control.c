/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 13:20:47 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/14 23:24:24 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./simulation.h"
#include "../dependencies.h"

static  bool _routine_wait(pthread_cond_t *cond, pthread_mutex_t *mutex,
		t_timespec *abstime, bool* is_running)
{
	int timeout_code;

	while(1)
	{
		timeout_code = pthread_cond_timedwait(cond, mutex, abstime);
		if (*is_running == false)
			return (1);
		if (!timeout_code)
			continue;
	}
	return (0);
}

// NOTE: the way we cache value of running, unlock, then rueturn, is sus.
//
// NOTE: we no longer check "STAT" because wei'll always have to return something
static bool	_simulation_runtime_handler(short choice, t_timespec *abstime)
{
	static pthread_mutex_t	run_mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	run_call = PTHREAD_COND_INITIALIZER;
	static bool				is_running = false;
	bool					ret_val;

	pthread_mutex_lock(&run_mutex);
	ret_val = is_running;
	if(choice != STAT)
	{
		if (choice == WAITRUN)
			while (is_running == false)
				pthread_cond_wait(&run_call, &run_mutex);
		else if (choice == WAITSTP)
		{
			ret_val = _routine_wait(&run_call, &run_mutex, abstime, &is_running);
			return (pthread_mutex_unlock(&run_mutex), ret_val);
		}
		else if (choice == TOGGLE)
		{
			pthread_cond_broadcast(&run_call);
			is_running = !ret_val;
		}
	}
	return (pthread_mutex_unlock(&run_mutex), ret_val);
}

void	sim_toggle(void)
{
	_simulation_runtime_handler(TOGGLE, NULL);
}

void	sim_wait_run(void)
{
	_simulation_runtime_handler(WAITRUN, NULL);
}

void	sim_routine_wait(t_timespec abstime)
{
	_simulation_runtime_handler(WAITSTP, &abstime);
}

bool	sim_get_status(void)
{
	return (_simulation_runtime_handler(STAT, NULL));
}
