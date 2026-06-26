/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 16:45:39 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"
#include <pthread.h>

static void	coder_post_creation_action(t_coder *self)
{
	int		sleep_time;
	bool	nigger;

	sleep_time = self->sim->params.time_to_compile
		+ self->sim->params.dongle_cooldown;
	nigger = self->id % 2;

	while (!self->sim->running)
		pthread_cond_wait(&self->birth_control, &self->sim->running_mutex);
	if (!nigger)
		return;
	while (!self->sim->running)
		sleep(sleep_time);
}

static void	init_routine_arr(void (**routines)(t_coder *))
{
	routines[0] = compile;
	routines[1] = debug;
	routines[2] = refactor;
}

void	*coder_routine(void *coder_p)
{
	t_coder	*self;
	int		routine_turn;
	void	(*routines[3])(t_coder *);

	self = coder_p;
	init_routine_arr(routines);
	coder_post_creation_action(self);
	routine_turn = 0;
	while (self->sim->running)
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++ - 1 % 3](self);
	}
	return (NULL);
}
