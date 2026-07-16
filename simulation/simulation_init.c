/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:15:04 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/16 00:19:58 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "simulation.h"

static int	init_coders(t_sim *sim)
{
	int	order;

	order = 0;
	sim->coders = malloc(sizeof(t_coder) * sim->args.number_of_coders);
	if (!sim->coders)
		return (cleaner(sim), 12);
	while (order < sim->args.number_of_coders)
	{
		if (_fill_coder_vals(sim->coders + order, order, sim))
		{
			join_coders(sim->monitor.coders_threads,
				sim->init_records.c_thread_init_ok);
			return (cleaner(sim), 1);
		}
		order++;
	}
	return (0);
}

static int	init_monitor(t_sim *sim)
{
	int	order;
	int	coders_num;

	order = 0;
	coders_num = sim->args.number_of_coders;
	sim->monitor.monitor_router = malloc(sizeof(pthread_cond_t) * coders_num);
	sim->monitor.coders_threads = malloc(sizeof(pthread_t) * coders_num);
	if (!sim->monitor.monitor_router || !sim->monitor.coders_threads)
		return (cleaner(sim), 12);
	init_sim_ta(sim);
	while (order < coders_num)
	{
		if (pthread_cond_init(sim->monitor.monitor_router + order, NULL))
			return (cleaner(sim), 1);
		sim->init_records.m_cond_init_ok = ++order;
	}
	if (pthread_cond_init(&sim->monitor.general_cond, NULL))
		return (cleaner(sim), 1);
	sim->init_records.m_gcond_init_ok = 1;
	if (pthread_create(&sim->monitor.thread, NULL, monitor, sim))
		return (cleaner(sim), 1);
	return (0);
}

// NOTE: are we sure the dongle doesn't need the whole simulation struct?
static int	init_dongles(t_sim *sim)
{
	int	order;

	sim->dongles = malloc(sizeof(t_dongle) * sim->args.number_of_coders);
	if (!sim->dongles)
		return (cleaner(sim), 12);
	order = 0;
	while (order < sim->args.number_of_coders)
	{
		(sim->dongles + order)->id = order + 1;
		(sim->dongles + order++)->cooldown = sim->args.dongle_cooldown;
	}
	return (0);
}

int	init_simulation(t_sim *sim, char **argv)
{
	t_args	args;

	memset(sim, 0, sizeof(t_sim));
	if (getargs(argv, &args) || args.number_of_coders == 0)
		return (1);
	sim->args = args;
	clock_gettime(CLOCK_REALTIME, &sim->startup);
	if (init_dongles(sim) || init_monitor(sim) || init_coders(sim))
		return (1);
	preseed_dongles_heap(sim);
	return (0);
}
