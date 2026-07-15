/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 01:39:07 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

void	*coder_routine(void *coder_p)
{
	int		routine_turn;
	t_coder	*self;

	static void (*routines[3])(t_coder *) = {compile, debug, refactor};
	self = coder_p;
	routine_turn = 0;
	sim_wait_run();
	if (sim_get_status() && first_compile(self))
		routine_turn++;
	while (sim_get_status())
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++](self);
	}
	return (NULL);
}
