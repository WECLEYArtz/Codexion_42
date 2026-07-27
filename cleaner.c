/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 01:49:52 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coder/coder.h"
#include "dongle/dongle.h"
#include "monitor/monitor.h"
#include "simulation/simulation.h"

// PERF:	at this point give every coder its thread,
//			no need to keep it in the monitor
void	join_coders(t_coder *coder, pthread_t *coders_threads, int join_count)
{
	while (join_count)
	{
		pthread_cond_signal(&coder->dongle_r->cond);
		pthread_cond_signal(&coder->dongle_l->cond);
		pthread_join(*coders_threads, NULL);
		coders_threads++;
		coder++;
		join_count--;
	}
}

static void	_clean_monitor(t_monitor *monitor, t_init_records *rec)
{
	int	count;

	count = rec->m_cond_init_ok;
	while (count)
		pthread_cond_destroy(monitor->monitor_router + (count-- - 1));
	free(monitor->monitor_router);
}

static void	_clean_coders(t_coder *coders, t_init_records *rec)
{
	int	count;

	count = rec->c_mutex_init_ok;
	while (count)
		pthread_mutex_destroy(&(coders + (count-- - 1))->compiled_mutex);
	free(coders);
}


static void	_clean_dongles(t_dongle *dongles, t_init_records *rec)
{
	int	count;

	count = rec->d_cond_init_ok;
	while (count)
		pthread_cond_destroy(&(dongles + (count-- - 1))->cond);
	count = rec->d_mutex_init_ok;
	while (count)
		pthread_mutex_destroy(&(dongles + (count-- - 1))->mutex);
	free(dongles);
}

void	cleaner(t_sim *sim)
{
	t_init_records	*init_records;

	init_records = &sim->init_records;
	sim_action(END, NULL);
	join_coders(sim->coders,
			sim->monitor->coders_threads,
			init_records->c_thread_init_ok);
	_clean_monitor(sim->monitor, init_records);
	_clean_dongles(sim->dongles, init_records);
	_clean_coders(sim->coders, init_records);
	free(sim->monitor->coders_threads);
}
