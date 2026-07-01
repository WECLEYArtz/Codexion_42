/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/01 21:18:54 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "simulation/simulation.h"
#include <pthread.h>

static void	_uninit_and_free_monitor_router(t_monitor *monitor)
{
	int				destroy_count;
	pthread_cond_t	*monitor_router;

	monitor_router = monitor->monitor_router;
	destroy_count = monitor->cond_init_ok;
	while (destroy_count)
		pthread_cond_destroy(monitor_router + (destroy_count-- - 1));
	free(monitor->monitor_router);
}

void	join_coders_threads(t_monitor *monitor)
{
	int	join_count;

	join_count = monitor->coder_thread_init_ok;
	while (join_count)
		pthread_join(*(monitor->coders_threads + (join_count-- - 1)), NULL);
}

// NOTE: the cleaner must also wait for threads to finish before cleaning them
void	cleaner(t_sim *sim, int step)
{
	if (step >= 1)
		pthread_mutex_destroy(&sim->running_mutex);
	if (step >= 2)
		pthread_mutex_destroy(&sim->print_mutex);
	if (step >= 3)
		pthread_cond_destroy(&sim->birth_control);
	if (step >= 4)
		_uninit_and_free_monitor_router(&sim->monitor);
	free(sim->monitor.coders_burnout_heap);
	free(sim->monitor.coders_threads);
	free(sim->dongles);
	free(sim->coders);
}
