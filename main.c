/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/01 18:41:57 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "simulation/simulation.h"

static void	lauch_simulation(t_sim *sim)
{
	pthread_mutex_lock(&sim->running_mutex);
	sim->running = true;
	gettimeofday(&sim->startup, NULL);
	pthread_cond_broadcast(&sim->birth_control);
	pthread_mutex_unlock(&sim->running_mutex);
}

int	main(int argc, char **argv)
{
	t_sim		sim;

	if (argc != 9 || init_simulation(&sim, argv))
		return (1);
	else
	{
		lauch_simulation(&sim);
		pthread_join(sim.monitor.thread, NULL);
		cleaner(&sim, INT_MAX);
	}
}
