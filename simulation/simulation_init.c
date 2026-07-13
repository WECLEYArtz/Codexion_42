/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:15:04 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/13 20:21:11 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "simulation.h"

static int	_fill_coder_vals(t_coder *coder, int order, t_sim *sim)
{
	int	mod;

	mod = sim->args.number_of_coders;
	coder->id = order + 1;
	coder->compiled = 0;
	coder->dongle_r = sim->dongles + (order);
	coder->dongle_l = sim->dongles + ((order + 1) % mod);
	coder->monitor_link = sim->monitor.monitor_router + order;
	coder->sim = sim;
	coder->burnout_node.previous = NULL;
	coder->burnout_node.next = NULL;
	coder->burnout_node.coder = coder;
	if (pthread_mutex_init(&coder->compiled_mutex, NULL))
		return (1);
	sim->init_records.c_mutex_init_ok++;
	if (pthread_create(sim->monitor.coders_threads + order, NULL, coder_routine,
			coder))
		return (1);
	sim->init_records.c_thread_init_ok++;
	return (0);
}

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
			join_coders(&sim->monitor, sim->init_records.c_thread_init_ok);
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

	sim->monitor.ta_burnout.sec = sim->args.time_to_burnout/1000;
	sim->monitor.ta_burnout.usec = (sim->args.time_to_burnout%1000)*1000;

	sim->monitor.ta_compile.sec = sim->args.time_to_compile/1000;
	sim->monitor.ta_compile.usec = (sim->args.time_to_compile%1000)*1000;

	sim->monitor.ta_debug.sec = sim->args.time_to_debug/1000;
	sim->monitor.ta_debug.usec = (sim->args.time_to_debug%1000)*1000;

	sim->monitor.ta_refactor.sec = sim->args.time_to_refactor/1000;
	sim->monitor.ta_refactor.usec = (sim->args.time_to_refactor%1000)*1000;

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
		(sim->dongles + order)->id = order+1;
		(sim->dongles + order++)->cooldown = sim->args.dongle_cooldown;
	}
	return (0);
}

int	init_simulation(t_sim *sim, char **argv)
{
	t_args	args;

	memset(sim, 0, sizeof(t_sim));
	if (getargs(argv, &args) || args.number_of_coders == 0
			|| gettimeofday(&sim->startup, NULL))
		return (1);
	sim->args = args;
	if (init_dongles(sim) || init_monitor(sim) || init_coders(sim))
		return (1);
	preseeder(sim);
	return (0);
}
