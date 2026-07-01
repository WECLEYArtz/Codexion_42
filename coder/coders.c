/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/01 18:15:29 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

static void	_coder_post_creation_action(t_sim *sim, int id)
{
	int	hold_sleep_time;

	if (sim->params.number_of_coders == 1)
		return ;
	hold_sleep_time = (sim->params.time_to_compile
			+ sim->params.dongle_cooldown) * 1000;
	pthread_mutex_lock(&sim->running_mutex);
	while (sim->running == false)
		pthread_cond_wait(&sim->birth_control, &sim->running_mutex);
	pthread_mutex_unlock(&sim->running_mutex);
	if (id % 2 == 0)
		return ;
	usleep(hold_sleep_time);
}

void	*coder_routine(void *coder_p)
{
	t_coder	*self;
	t_sim	*sim;
	int		routine_turn;

	self = coder_p;
	sim = self->sim;
	routine_turn = 0;
	_coder_post_creation_action(self->sim ,self->id);
	while (self->sim->running)
	{
		if (routine_turn == 3)
			routine_turn = 0;
		sim->routines[routine_turn++](self);
	}
	announce(self, "[DEBUG] is exiting...");
	return (NULL);
}
