/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/13 01:58:51 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// printf("Last		compile - p:%ld n:%ld\n",
// 		target_coder->last_compile.tv_sec, target_coder->last_compile.tv_usec);
// printf("Deadline	compile - p:%ld n:%ld\n",
// 		timeout.tv_sec, timeout.tv_nsec);

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../simulation/simulation.h"

static int	wait_coder_burnout(t_coder *target_coder, t_timeoutadd *timeoutadd)
{
	int				old_compiles;
	int				rc;
	struct timespec	timeout;

	if (DEBUG)
		puts(RED "[MONITOR] Locking Mutex CMPL" RESET);
	pthread_mutex_lock(&target_coder->compiled_mutex);
	old_compiles = target_coder->compiled;
	
	timeout.tv_sec = target_coder->last_compile.tv_sec + timeoutadd->sec;
	timeout.tv_nsec = (target_coder->last_compile.tv_usec + timeoutadd->usec) * 1000;
    timeout.tv_sec += timeout.tv_nsec / 1000000000;  
    timeout.tv_nsec = timeout.tv_nsec % 1000000000;  

	// printf("[MONITOR] waiting burnout using %p\n", target_coder->monitor_link);
	while(1)
	{

		if (DEBUG)
			puts(GREEN "[debug] [MONITOR] UnLocking Mutex CMPL (CondW)" RESET);
		rc = pthread_cond_timedwait(target_coder->monitor_link,
				&target_coder->compiled_mutex, &timeout);
		if (DEBUG)
			puts(RED "[debug] [MONITOR] Locking Mutex CMPL (CondW)" RESET);
		if (!rc && old_compiles == target_coder->compiled)
			continue;
		else if (rc && old_compiles == target_coder->compiled)
		{
			// announce(target_coder, "Failed to compile [MONITOR] ---");

			if (DEBUG)
				puts(GREEN "[debug] [MONITOR] Unlocking Mutex CMPL" RESET);

			announce(target_coder, "has burnouted");
			pthread_mutex_unlock(&target_coder->compiled_mutex);
			return(1);
		}
		else
		{
			if (DEBUG)
				puts(GREEN "[debug] [MONITOR] Unlocking Mutex CMPL" RESET);
			pthread_mutex_unlock(&target_coder->compiled_mutex);
			return(0);
		}
	}
}

void	*monitor(void *t_sim_p)
{
	t_sim			*sim;
	t_monitor		*monitor;
	t_coder			*target_coder;
	t_timeoutadd	*timeoutadd;

	sim = t_sim_p;
	monitor = &sim->monitor;
	timeoutadd = &monitor->timeoutadd;
	burnoutpq_monitor_watch(monitor);
	target_coder = burnoutpq_pop();
	while (!wait_coder_burnout(target_coder, timeoutadd))
		target_coder = burnoutpq_pop();
	sim_stop();
	join_coders(&sim->monitor, sim->init_records.c_thread_init_ok);
	return (NULL);
}
