/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:15:04 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 20:31:06 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "simulation.h"

static int	_fill_coder_vals(t_coder *coder, int order, t_sim *sim)
{
	int	mod;

	mod = sim->params.number_of_coders;
	coder->id = order + 1;
	coder->time_to_burnout = sim->params.time_to_burnout;
	coder->dongle_l = sim->dongles + (order);
	coder->dongle_r = sim->dongles + (order + 1 % mod);
	coder->sim = sim;
	if (pthread_create(&(coder->thread), NULL, coder_routine, coder))
		return (1);
	return (0);
}

static int	init_coders(t_sim *sim)
{
	int	order;

	order = 0;
	sim->coders = malloc(sizeof(t_coder) * sim->params.number_of_coders);
	if (!sim->coders)
		return (simcleaner(sim, INT_MAX), 1);
	while (order < sim->params.number_of_coders)
	{
		if (_fill_coder_vals(sim->coders + order, order, sim))
			return (simcleaner(sim, INT_MAX), 1);
		order++;
	}
	return (0);
}

static int	init_dongles(t_sim *sim)
{
	int	order;

	sim->dongles = malloc(sizeof(t_dongle) * sim->params.number_of_coders);
	if (!sim->dongles)
		return (simcleaner(sim, INT_MAX), 1);
	order = 0;
	while (order < sim->params.number_of_coders)
		(sim->dongles + order++)->cooldown = sim->params.dongle_cooldown;
	return (0);
}

// NOTE:	do i need this when we clear once for all
//			before closing the whole program?
//			do i need to go back to simple?
static int	init_condv_and_mutex(t_sim *sim)
{
	if (pthread_mutex_init(&sim->running_mutex, NULL))
		return (simcleaner(sim, 1), 1);
	if (pthread_mutex_init(&sim->print_mutex, NULL))
		return (simcleaner(sim, 1), 2);
	if (pthread_cond_init(&sim->birth_control, NULL))
		return (simcleaner(sim, 1), 3);
	return (0);
}

int	init_simulation(t_sim *sim, char **argv)
{
	t_params	params;

	if (getparams(argv, &params) || params.number_of_coders == 0)
		return (1);
	sim->params = params;
	sim->routines[0] = compile;
	sim->routines[1] = debug;
	sim->routines[2] = refactor;
	sim->running = false;
	if (init_condv_and_mutex(sim) || init_dongles(sim) || init_coders(sim))
		return (1);
	return (0);
}
