/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/13 00:20:45 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

void	*coder_routine(void *coder_p)
{
	int						routine_turn;
	t_coder					*self;
	static void (*routines[3])(t_coder *) = {compile, debug, refactor};
	self = coder_p;
	routine_turn = 0;
	sim_launch_hold();


	if (sim_running_status())
		first_compile(self);

	// printf("[CODER]: will listen on privat %p\n", self->monitor_link);
	while (sim_running_status())
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++](self);
	}
	puts("Exiting...");
	return (NULL);
}
