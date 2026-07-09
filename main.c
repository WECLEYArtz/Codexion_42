/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/08 21:40:20 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"
#include "simulation/simulation.h"

int	main(int argc, char **argv)
{
	t_sim	sim;

	if (argc != 9 || init_simulation(&sim, argv))
		return (1);
	else
	{
		sim_lauch_run();
		pthread_join(sim.monitor.thread, NULL);
		cleaner(&sim);
	}
}
