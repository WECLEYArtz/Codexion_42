/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 15:58:41 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../simulation/simulation.h"

static int	wait_coder_burnout(t_coder *coder, t_timeadd *ta_burnout)
{
	int			old_compiles;
	int			rc;
	t_timespec	abstime;

	pthread_mutex_lock(&coder->compiled_mutex);
	old_compiles = coder->compiled;
	abstime = get_abstime(&coder->last_compile, ta_burnout);
	while (1)
	{
		rc = pthread_cond_timedwait(coder->monitor_link,
				&coder->compiled_mutex,
				&abstime);
		if (!rc && old_compiles == coder->compiled)
			continue ;
		else if (rc && old_compiles == coder->compiled)
		{
			pthread_mutex_unlock(&coder->compiled_mutex);
			sim_toggle(OFF);
			announce(coder, RED "has burnouted" RESET, 1);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&coder->compiled_mutex);
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
	while (!wait_coder_burnout(burnoutpq_pop(), &sim->ta_burnout))
		;
	join_coders(monitor->coders_threads, sim->init_records.c_thread_init_ok);
	return (NULL);
}
