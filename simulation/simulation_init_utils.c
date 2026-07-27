/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_init_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:48:08 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 03:32:53 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "simulation.h"

void	__init_ta(t_time_add *time, int ms)
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

int	_create_coder(t_coder *coder, int order, t_sim *sim)
{
	coder->id = order + 1;
	coder->compiled = 0;
	coder->dongle_r = sim->dongles + order;
	coder->dongle_l = sim->dongles + (order + 1) % sim->args.number_of_coders;
	coder->monitor_link = sim->monitor->monitor_router + order;
	coder->first_compiler = false;
	coder->previous = NULL;
	coder->next = NULL;
	coder->sim = sim;
	if (pthread_mutex_init(&coder->compiled_mutex, NULL))
		return (1);
	sim->init_records.c_mutex_init_ok++;
	if (pthread_create(&coder->thread, NULL, coder_routine, coder))
		return (1);
	sim->init_records.c_thread_init_ok++;
	return (0);
}

void	preseed_coders_firstcompile(t_sim *sim)
{
	int		i;
	int		coders_count;
	t_coder	*coder;

	i = 1;
	coders_count = sim->args.number_of_coders;
	coder = sim->coders;
	while (i < coders_count)
	{
		coder_dates_update(coder + i);
		i += 2;
	}
	i = 0;
	while (i < coders_count)
	{
		coder_dates_update(coder + i);
		i += 2;
	}
}

void	preseed_dongles_heap(t_sim *sim)
{
	int		i;
	int		coders_count;
	t_coder	*coder;
	short	priority_order;

	priority_order = 0;
	coders_count = sim->args.number_of_coders;
	coder = sim->coders;
	i = 1;
	while (priority_order < 2)
	{
		while (i < coders_count)
		{
			(coder + i)->dongle_r->heap[priority_order] = coder + i;
			(coder + i)->dongle_l->heap[priority_order] = coder + i;
			i += 2;
		}
		i = 0 + 2 * (coders_count > 2 && coders_count % 2);
		priority_order++;
	}
	if (coders_count > 2 && coders_count % 2)
	{
		(coder)->dongle_r->heap[0] = coder;
		(coder)->dongle_l->heap[1] = coder;
	}
}
