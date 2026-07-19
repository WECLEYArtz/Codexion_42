/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 17:38:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "monitor/monitor.h"
#include "simulation/simulation.h"
#include "utils/utils.h"

int	main(int argc, char **argv)
{
	t_sim		sim;
	t_monitor	monitor;

	if (argc != 9 || init_simulation(&sim, &monitor, argv))
		return (1);
	else
	{
		sim_action(ON, NULL);
		clock_gettime(CLOCK_REALTIME, &sim.startup);
		pthread_join(monitor.thread, NULL);
		cleaner(&sim);
	}
}

// try:	./codexion 40 300 100 100 100 7 0 edf
// try: valgrind --tool=helgrind ./codexion 200 301 100 100 100 7 0 edf
// try ./codexion 400 202 1 100 100 7 0 edf (may deadlock)
