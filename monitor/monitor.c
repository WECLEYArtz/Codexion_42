/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/14 03:27:28 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../simulation/simulation.h"

static int	wait_coder_burnout(t_coder *target_coder, t_timeadd *ta_burnout)
{
	int				old_compiles;
	int				rc;
	struct timespec	timeout;

	// if (DEBUG) puts(RED "[MONITOR] Locking Mutex CMPL" RESET);
	pthread_mutex_lock(&target_coder->compiled_mutex);
	old_compiles = target_coder->compiled;
	timeout.tv_sec = target_coder->last_compile.tv_sec + ta_burnout->sec;
	timeout.tv_nsec = (target_coder->last_compile.tv_usec + ta_burnout->usec)
		* 1000;
	timeout.tv_sec += timeout.tv_nsec / 1000000000;
	timeout.tv_nsec = timeout.tv_nsec % 1000000000;
	while (1)
	{
		// if (DEBUG) puts(GREEN "[debug] [MONITOR] UnLocking Mutex CMPL (CondW)" RESET);
		rc = pthread_cond_timedwait(target_coder->monitor_link,
				&target_coder->compiled_mutex, &timeout);
		// if (DEBUG) puts(RED "[debug] [MONITOR] Locking Mutex CMPL (CondW)" RESET);
		if (!rc && old_compiles == target_coder->compiled)
			continue ;
		else if (rc && old_compiles == target_coder->compiled)
		{
			// if (DEBUG) puts(GREEN "[debug] [MONITOR] Unlocking Mutex CMPL" RESET);
			announce(target_coder, "has burnouted");
			pthread_mutex_unlock(&target_coder->compiled_mutex);
			return (1);
		}
		else
		{
			// if (DEBUG) puts(GREEN "[debug] [MONITOR] Unlocking Mutex CMPL" RESET);
			pthread_mutex_unlock(&target_coder->compiled_mutex);
			return (0);
		}
	}
}

void	*monitor(void *t_sim_p)
{
	t_sim		*sim;
	t_monitor	*monitor;

	sim = t_sim_p;
	monitor = &sim->monitor;
	burnoutpq_monitor_watch(monitor);
	while (!wait_coder_burnout(burnoutpq_pop(), &monitor->ta_burnout)) ;
	sim_stop();
	join_coders(monitor->coders_threads, sim->init_records.c_thread_init_ok);
	return (NULL);
}
