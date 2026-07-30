/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:15:04 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 18:57:23 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../utils/utils.h"
#include "simulation.h"

static int	init_coders(t_sim *sim)
{
	int	order;
	int	coders_num;

	order = 0;
	coders_num = sim->args.number_of_coders;
	sim->coders = malloc(sizeof(t_coder) * coders_num);
	if (!sim->coders)
		return (12);
	while (order < coders_num)
	{
		if (_create_coder(sim->coders + order, order, sim))
			return (1);
		order++;
	}
	return (0);
}

static int	init_monitor(t_sim *sim, t_monitor *monitor)
{
	int	order;
	int	coders_num;

	order = 0;
	coders_num = sim->args.number_of_coders;
	memset(monitor, 0, sizeof(t_monitor));
	monitor->monitor_router = malloc(sizeof(pthread_cond_t) * coders_num);
	if (!monitor->monitor_router)
		return (12);
	while (order < coders_num)
	{
		if (pthread_cond_init(monitor->monitor_router + order, NULL))
			return (1);
		sim->init_records.m_cond_init_ok = ++order;
	}
	return (0);
}

// NOTE: dont forget to put dongle initialisation in subfunction
static int	init_dongles(t_sim *sim)
{
	int	order;
	int	coders_num;

	coders_num = sim->args.number_of_coders;
	sim->dongles = malloc(sizeof(t_dongle) * coders_num);
	if (!sim->dongles)
		return (12);
	order = 0;
	while (order < coders_num)
		if (_init_dongle(order++, sim))
			return (1);
	return (0);
}

int	init_simulation(t_sim *sim, t_monitor *monitor, char **argv)
{
	t_args	args;

	memset(sim, 0, sizeof(t_sim));
	if (get_args(argv, &args) || args.number_of_coders == 0)
		return (1);
	sim->args = args;
	sim->monitor = monitor;
	sim->unfinished_coders = args.number_of_coders;
	_init_sim_ta(sim);
	if (pthread_mutex_init(&sim->unfinished_coders_mutex, NULL))
		return (cleaner(sim), 1);
	else
		sim->init_records.s_mutex_init_ok = 1;
	if (init_dongles(sim) || init_monitor(sim, monitor) || init_coders(sim)
		|| pthread_create(&monitor->thread, NULL, monitor_routine, sim))
		return (cleaner(sim), 1);
	preseed_dongles_heap(sim);
	preseed_coders_firstcompile(sim);
	return (0);
}
