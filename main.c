/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 16:40:36 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "parser/parser.h"
#include "simulation/simulation.h"
#include <pthread.h>

// Initialise the simulation,
// - create the simulation structure.
// - allocate the needed size to fill up with all coders, indexed by their id.
// - get the parsed parameters.
// - initialise the mutexes to be used later.

static void	debug(t_sim sim)
{
	printf("\
	number_of_coders : %d \n\
	time_to_burnout : %d \n\
	time_to_compile : %d \n\
	time_to_debug : %d \n\
	time_to_refactor : %d \n\
	number_of_compiles_required : %d \n\
	dongle_cooldown : %d \n\
	scheduler : %d where (1)edf - (2)fifo \n",
		sim.params.number_of_coders,
		sim.params.time_to_burnout,
		sim.params.time_to_compile,
		sim.params.time_to_debug,
		sim.params.time_to_refactor,
		sim.params.number_of_compiles_required,
		sim.params.dongle_cooldown,
		sim.params.scheduler);
}

int	main(int argc, char **argv)
{
	t_sim		sim;
	t_params	params;
	pthread_cond_t birth_control;

	if (argc != 9)
		return (-1);
	params = getparams(argv);
	sim = init_simulation(params);

	//bad way to start testing hh, (where is mutex locking man)
	sim.running = true;
	pthread_cond_broadcast(&sim.birth_control);
	sleep(10);
	sim.running = false;

	debug(sim);
	sim_cleaner(&sim);
}
