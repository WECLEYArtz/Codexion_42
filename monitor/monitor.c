/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/09 00:27:55 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../simulation/simulation.h"



void	*monitor(void *t_sim_p)
{
	t_sim	*sim;

	sim = t_sim_p;
	sim_launch_hold();

	// MONITOR LOGIC GOES HERE
	sleep(3);
	sim_stop();
	join_coders(&sim->monitor, sim->init_records.c_thread_init_ok);
	// MONITOR LOGIC GOES HERE

	return (NULL);
}
