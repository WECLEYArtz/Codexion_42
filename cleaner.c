/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/08 22:01:10 by ahmounsi         ###   ########.fr       */
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
	while (destroy_count)
		pthread_cond_destroy(monitor_router + (destroy_count-- - 1));
	free(monitor->monitor_router);
}

// NOTE: the cleaner must also wait for threads to finish before cleaning them
void	cleaner(t_sim *sim)
{
	_clean_monitor_router(&sim->monitor, sim->init_records.m_cond_init_ok);
	free(sim->monitor.coders_threads);
	free(sim->dongles);
	free(sim->coders);
}
