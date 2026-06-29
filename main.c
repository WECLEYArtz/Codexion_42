/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 17:12:19 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "simulation/simulation.h"
#include <pthread.h>

static void	lauch_simulation(t_sim *sim)
{
	if (pthread_mutex_lock(&sim->running_mutex))
		simcleaner(sim, 4);
	sim->running = true;
	if (gettimeofday(&sim->startup, NULL)
		|| pthread_cond_broadcast(&sim->birth_control)
		|| pthread_mutex_unlock(&sim->running_mutex))
		simcleaner(sim, 4);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 9 || init_simulation(&sim, argv))
		return (1);
	else
	{
		lauch_simulation(&sim);
		sleep(10); // debug
		sim.running = false;
		simcleaner(&sim, 4);
	}
}
