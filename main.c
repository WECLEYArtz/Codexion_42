/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/27 19:32:24 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.c"
#include "dependencies.h"
#include "simulation/simulation.h"
#include <pthread.h>

// Initialise the simulation,
// - create the simulation structure.
// - allocate the needed size to fill up with all coders, indexed by their id.
// - get the parsed parameters.
// - initialise the mutexes to be used later.

static void lauch_simulation(t_sim *sim)
{
	sleep(1);
	db_announce(sim, "[SIM] taking mutex"); // debug

	pthread_mutex_lock(&sim->running_mutex);
	sim->running = true;

 	db_announce(sim, "[SIM] broadcasting..."); // debug

	gettimeofday(&sim->startup, NULL);
	pthread_cond_broadcast(&sim->birth_control);
	pthread_mutex_unlock(&sim->running_mutex);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 9)
		return (-1);
	init_simulation(&sim, argv); // all coder created here
	printf("sim pointer is : %p\n", &sim); // debug

	lauch_simulation(&sim);
	sleep(10); //debug
	sim.running = false; // end of simulation
	db_announce(&sim, "ending simulation..."); // debug
	sim_cleaner(&sim);
}
