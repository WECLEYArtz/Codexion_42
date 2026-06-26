/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:15:04 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 16:16:28 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../parser/parser.h"
#include "simulation.h"

static void	_fill_coder_vals(t_coder *coder, int order, t_sim *sim)
{
	int		mod;

	mod = sim->params.number_of_coders;
	coder->id = order + 1;
	coder->time_to_burnout = sim->params.time_to_burnout;
	coder->dongle_l = sim->dongles + (order);
	coder->dongle_r = sim->dongles + (order + 1 % mod);
	coder->sim = sim;
	coder->birth_control = sim->birth_control;
	if (pthread_create(&(coder->thread), NULL, coder_routine, coder))
	{
		sim_cleaner(sim);
		exit(puts("DEBUG: Failed to create a thread"));
	}
}

static void	init_coders(t_sim *sim)
{
	int		order;

	order = 0;
	sim->coders = malloc(sizeof(t_coder) * sim->params.number_of_coders);
	if (!sim->coders)
	{
		sim_cleaner(sim);
		exit(puts("DEBUG: Failed allocation, must clean"));
	}
	while (order < sim->params.number_of_coders)
	{
		_fill_coder_vals(sim->coders + order, order, sim);
		order ++;
	}
}

static void	init_dongles(t_sim *sim)
{
	int	order;

	sim->dongles = malloc(sizeof(t_dongle) * sim->params.number_of_coders);
	if (!sim->dongles)
	{
		sim_cleaner(sim);
		exit(puts("DEBUG: Failed allocation, must clean"));
	}
	order = 0;
	while (order < sim->params.number_of_coders)
		(sim->dongles + order++)->cooldown = sim->params.dongle_cooldown;
}

static void init_metex(t_sim *sim)
{
	if (pthread_mutex_init(&sim->running_mutex, NULL)	||
			pthread_mutex_init(&sim->birth_mutex, NULL) ||
			pthread_mutex_init(&sim->print_mutex, NULL))
	{
		sim_cleaner(sim);
		exit(puts("DEBUG: Failed mutex init, must clean"));
	}
}

t_sim	init_simulation(t_params params)
{
	t_sim	sim;

	sim.params = params;
	init_dongles(&sim);
	init_coders(&sim);
	init_metex(&sim);
	sim.running = false;
	sim.birth_wake = false;
	return (sim);
}
