/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/07 15:51:22 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

static void	_coder_post_creation_action(t_sim *sim, int id)
{
	int	hold_time;

	if (sim->args.number_of_coders == 1)
		return ;
	hold_time = (sim->args.time_to_compile + sim->args.dongle_cooldown) * 1000;
	sim_launch_hold();
	if (id % 2 == 0)
		return ;
	usleep(hold_time);
}

void	*coder_routine(void *coder_p)
{
	t_coder	*self;
	t_sim	*sim;
	int		routine_turn;

	static void (*routines[3])(t_coder *) = {compile, debug, refactor};
	self = coder_p;
	sim = self->sim;
	routine_turn = 0;
	_coder_post_creation_action(self->sim, self->id);
	while (sim_running_status())
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++](self);
	}
	return (NULL);
}
