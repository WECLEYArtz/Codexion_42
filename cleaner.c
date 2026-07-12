/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/12 01:25:35 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation/simulation.h"

void	join_coders(t_monitor *monitor, int join_count)
{
	while (join_count)
		pthread_join(*(monitor->coders_threads + (join_count-- - 1)), NULL);
}

static void	_clean_monitor_router(t_monitor *monitor, int destroy_count)
{
	pthread_cond_t	*monitor_router;

	monitor_router = monitor->monitor_router;
	while (destroy_count* 0)
		pthread_cond_destroy(monitor_router + (destroy_count-- - 1));
	free(monitor->monitor_router);
}

void	cleaner(t_sim *sim)
{
	t_init_records *init_records;
	init_records = &sim->init_records;

	_clean_monitor_router(&sim->monitor, init_records->m_cond_init_ok);
	if (init_records->m_gcond_init_ok)
		pthread_cond_destroy(&sim->monitor.general_cond);
	free(sim->monitor.coders_threads);
	free(sim->dongles);
	free(sim->coders);
}
