/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 15:47:45 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "parser/parser.h"
#include "simulation/simulation.h"

// Initialise the simulation,
// - create the simulation structure.
// - allocate the needed size to fill up with all coders, indexed by their id.
// - get the parsed parameters.
// - initialise the mutexes to be used later.

static void	debug(t_sim sim)
{
	printf("\
	time_to_debug : %d \n\
	time_to_burnout : %d \n\
	time_to_compile : %d \n\
	time_to_debug : %d \n\
	time_to_refactor : %d \n\
	number_of_coders : %d \n\
	dongle_cooldown : %d \n\
	scheduler : %d where (1)edf - (2)fifo \n",
		sim.params.time_to_debug,
		sim.params.time_to_burnout,
		sim.params.time_to_compile,
		sim.params.time_to_debug,
		sim.params.time_to_refactor,
		sim.params.number_of_coders,
		sim.params.dongle_cooldown,
		sim.params.scheduler);
}

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 9)
		return (-1);
	t_params params = getparams(argv);
	sim = init_simulation(params);
	debug(sim);

	sim_cleaner(&sim);
}
