/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:48:08 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/14 01:08:58 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "simulation.h"

void	_init_ta(t_timeadd *time, int ms)
{
	time->sec = ms / 1000;
	time->usec = (ms % 1000) * 1000;
}

int	_fill_coder_vals(t_coder *coder, int order, t_sim *sim)
{
	coder->id = order + 1;
	coder->compiled = 0;
	coder->dongle_r = sim->dongles + order;
	coder->dongle_l = sim->dongles + (order + 1) % sim->args.number_of_coders;
	coder->monitor_link = sim->monitor.monitor_router + order;
	coder->burnout_node.coder = coder;
	coder->sim = sim;
	if (pthread_mutex_init(&coder->compiled_mutex, NULL))
		return (1);
	sim->init_records.c_mutex_init_ok++;
	if (pthread_create(sim->monitor.coders_threads + order, NULL, coder_routine,
			coder))
		return (1);
	sim->init_records.c_thread_init_ok++;
	return (0);
}
