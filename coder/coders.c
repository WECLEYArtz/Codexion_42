/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/21 16:02:02 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../utils/utils.h"
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
	coder_dates_update(self);
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

//	The function responsible for updating last compile and burnout date
//	called everytime a coder compiles
//	and once when the coder is first created
void	coder_dates_update(t_coder *coder)
{
	clock_gettime(CLOCK_REALTIME, &coder->last_compile);
	coder->burnout_date = get_abstime(
			&coder->last_compile,
			&coder->sim->ta_burnout);
}
