/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:37:01 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/31 17:47:49 by ahmounsi         ###   ########.fr       */
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
		sim_action(ON, &sim.startup);
		pthread_join(monitor.thread, NULL);
		cleaner(&sim);
	}
}
