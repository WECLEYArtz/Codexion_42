/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/01 21:10:32 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../simulation/simulation.h"

static void	_monitor_post_creation_wait(t_sim *sim)
{
	pthread_mutex_lock(&sim->running_mutex);
	while (sim->running == false)
		pthread_cond_wait(&sim->birth_control, &sim->running_mutex);
	pthread_mutex_unlock(&sim->running_mutex);
}

void	*monitor(void *t_sim_p)
{
	t_sim	*sim;

	sim = t_sim_p;
	puts("[MONITOR DEBUG]: monitor created");
	_monitor_post_creation_wait(sim);

	// MONITOR LOGIC GOES HERE
	sleep(5);
	pthread_mutex_lock(&sim->running_mutex);
	sim->running = false;
	pthread_mutex_unlock(&sim->running_mutex);
	join_coders_threads(&sim->monitor);
	// MONITOR LOGIC GOES HERE

	puts("[MONITOR] is exiting...");
	return (NULL);
}
