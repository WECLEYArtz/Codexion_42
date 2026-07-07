/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/07 14:24:17 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../simulation/simulation.h"
#include "launch_handler.h"

void	*monitor(void *t_sim_p)
{
	t_sim	*sim;

	sim = t_sim_p;
	sim_launch_hold();


	// MONITOR LOGIC GOES HERE
	sleep(5);
	sim_stop();
	join_coders_threads(&sim->monitor);
	// MONITOR LOGIC GOES HERE


	return (NULL);
}
