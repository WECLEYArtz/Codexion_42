/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 16:01:24 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation/simulation.h"
#include "coder/coder.h"

void	join_coders(pthread_t *coders_threads, int join_count)
{
	sim_toggle(OFF);
	while (join_count)
		pthread_join(*(coders_threads + (join_count-- - 1)), NULL);
}

static void	_clean_monitor(t_monitor *monitor, t_init_records *rec)
{
	int	count;

	count = rec->m_cond_init_ok;
	while (count)
		pthread_cond_destroy(monitor->monitor_router + (count-- - 1));
	free(monitor->monitor_router);
	if (rec->m_gcond_init_ok)
		pthread_cond_destroy(&monitor->general_cond);
}

static void	_clean_coders(t_coder *coders, t_init_records *rec)
{
	int	count;

	count = rec->c_mutex_init_ok;
	while (count)
		pthread_mutex_destroy(&(coders+(count-- -1))->compiled_mutex);
	free(coders);
}

void	cleaner(t_sim *sim)
{
	t_init_records	*init_records;
	init_records = &sim->init_records;

	_clean_monitor(&sim->monitor, init_records);
	_clean_coders(sim->coders, init_records);
	free(sim->monitor.coders_threads);
	free(sim->dongles);
}
