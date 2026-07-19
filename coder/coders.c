/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 16:41:58 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

void	*coder_routine(void *coder_p)
{
	static void	(*routines[3])(t_coder *) = {compile, debug, refactor};
	int			routine_turn;
	t_coder		*self;

	routine_turn = 0;
	self = (t_coder *)coder_p;
	if (!sim_action(WAIT_RUN, NULL))
		return (NULL);
	if (first_compile(self))
		routine_turn++;
	while (sim_action(STAT, NULL) == ON)
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++](self);
	}
	return (NULL);
}
