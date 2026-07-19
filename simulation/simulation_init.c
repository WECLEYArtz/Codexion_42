/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:15:04 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 17:15:47 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "../utils/utils.h"
#include "../monitor/monitor.h"
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

	memset(monitor, 0, sizeof(t_monitor));
	order = 0;
	coders_num = sim->args.number_of_coders;
	monitor->monitor_router = malloc(sizeof(pthread_cond_t) * coders_num);
	monitor->coders_threads = malloc(sizeof(pthread_t) * coders_num);
	if (!monitor->monitor_router || !monitor->coders_threads)
		return (12);
	while (order < coders_num)
	{
		if (pthread_cond_init(monitor->monitor_router + order, NULL))
			return (1);
		sim->init_records.m_cond_init_ok = ++order;
	}
	return (0);
}

// NOTE: are we sure the dongle doesn't need the whole simulation struct?
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
		(sim->dongles + order++)->cooldown = sim->args.dongle_cooldown;
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
	_init_sim_ta(sim);
	if (init_dongles(sim) || init_monitor(sim, monitor) || init_coders(sim)
		|| pthread_create(&monitor->thread, NULL, monitor_routine, sim))
	{
		return (1);
		cleaner(sim);
	}
	preseed_dongles_heap(sim);
	return (0);
}
