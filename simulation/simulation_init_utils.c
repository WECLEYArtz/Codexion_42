/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:48:08 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "simulation.h"

static void	__init_ta(t_time_add *time, int ms)
{
	time->sec = ms / 1000;
	time->nsec = (ms % 1000) * 1000000;
}

void	_init_sim_ta(t_sim *sim)
{
	__init_ta(&sim->ta_burnout, sim->args.time_to_burnout);
	__init_ta(&sim->ta_compile, sim->args.time_to_compile);
	__init_ta(&sim->ta_debug, sim->args.time_to_compile
		+ sim->args.time_to_debug);
	__init_ta(&sim->ta_refactor, sim->args.time_to_compile
		+ sim->args.time_to_debug + sim->args.time_to_refactor);
	__init_ta(&sim->ta_dongle_cooldown, sim->args.dongle_cooldown);
}

int	_init_dongle(int order, t_sim *sim)
{
	if (pthread_cond_init(&(sim->dongles + order)->cond, NULL))
		return (1);
	else
		sim->init_records.d_cond_init_ok++;
	if (pthread_mutex_init(&(sim->dongles + order)->mutex, NULL))
		return (1);
	else
		sim->init_records.d_mutex_init_ok++;
	(sim->dongles + order)->heap[0] = NULL;
	(sim->dongles + order)->heap[1] = NULL;
	(sim->dongles + order)->heap_elements = 2;
	(sim->dongles + order)->cooldown = sim->args.dongle_cooldown;
	(sim->dongles + order)->scheduler = sim->args.scheduler;
	(sim->dongles + order)->taken = false;
	clock_gettime(CLOCK_REALTIME, &(sim->dongles + order)->available_date);
	(sim->dongles + order)->sim = sim;
	return (0);
}

int	_create_coder(t_coder *coder, int order, t_sim *sim,
		void *(*routine)(void *))
{
	coder->id = order + 1;
	coder->compiles_required = sim->args.number_of_compiles_required + 1;
	coder->dongle_r = sim->dongles + order;
	coder->dongle_l = sim->dongles + (order + 1) % sim->args.number_of_coders;
	coder->monitor_link = sim->monitor->monitor_router + order;
	coder->previous = NULL;
	coder->next = NULL;
	coder->sim = sim;
	if (pthread_mutex_init(&coder->compiled_mutex, NULL))
		return (1);
	sim->init_records.c_mutex_init_ok++;
	if (pthread_create(&coder->thread, NULL, routine, coder))
		return (1);
	sim->init_records.c_thread_init_ok++;
	return (0);
}
