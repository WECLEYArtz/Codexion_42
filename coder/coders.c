/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 20:30:59 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"
#include <pthread.h>

// NOTE: if one coder, dont make it sleep...
static void	coder_post_creation_action(t_coder *self)
{
	int	hold_sleep_time;

	if (self->sim->params.number_of_coders == 1)
		return ;
	hold_sleep_time = (self->sim->params.time_to_compile
			+ self->sim->params.dongle_cooldown) * 1000;
	pthread_mutex_lock(&self->sim->running_mutex);
	while (self->sim->running == false)
		pthread_cond_wait(&self->sim->birth_control, &self->sim->running_mutex);
	pthread_mutex_unlock(&self->sim->running_mutex);
	if (self->id % 2 == 0)
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
	coder_post_creation_action(self);
	while (self->sim->running)
	{
		if (routine_turn == 3)
			routine_turn = 0;
		sim->routines[routine_turn++](self);
	}
	return (NULL);
}
