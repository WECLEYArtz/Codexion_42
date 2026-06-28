/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/28 12:28:28 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "simulation/simulation.h"
#include <pthread.h>

// Initialise the simulation,
// - create the simulation structure.
// - allocate the needed size to fill up with all coders, indexed by their id.
// - get the parsed parameters.
// - initialise the mutexes to be used later.

static void	lauch_simulation(t_sim *sim)
{
	sleep(1);
	if (pthread_mutex_lock(&sim->running_mutex))
		sim_cleaner(sim);
	sim->running = true;
	if (gettimeofday(&sim->startup, NULL)
		|| pthread_cond_broadcast(&sim->birth_control)
		|| pthread_mutex_unlock(&sim->running_mutex)) // here start the timer
		sim_cleaner(sim);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 9)
		return (-1);
	init_simulation(&sim, argv); // all coders created here
	lauch_simulation(&sim);                    // all coders launch here
	sleep(10);                                 // debug
	sim.running = false;                       // end of simulation
	sim_cleaner(&sim);
}
