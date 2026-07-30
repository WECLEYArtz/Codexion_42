/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 16:09:39 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../monitor/monitor.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"

//	Responsible for updating last compile and burnout date.
//	First called when the coder is created, then everytime a coder compiles.

// NOTE: if you can find a way to make sim accessible easielly 
void	coder_compiled_status_update(t_coder *coder)
{
	t_sim *sim;

	sim = coder->sim;
	clock_gettime(CLOCK_REALTIME, &coder->last_compile);
	coder->burnout_date = get_abstime(
			&coder->last_compile,
			&coder->sim->ta_burnout);
	coder->compiles_required--;
	if (coder->compiles_required == 0)
	{
		pthread_mutex_lock(&sim->unfinished_coders_mutex);
		printf(BLUE"[coder %d] i compiled, removing one unfinished from %d\n"RESET,
				coder->id, sim->unfinished_coders);
		sim->unfinished_coders--;
		pthread_mutex_unlock(&sim->unfinished_coders_mutex);
	}
}

void	*coder_routine(void *coder_p)
{
	static void	(*routines[3])(t_coder *) = {compile, debug, refactor};
	int			routine_turn;
	t_coder		*self;

	routine_turn = 0;
	self = (t_coder *)coder_p;
	if (sim_action(WAIT_RUN, NULL) == END)
		return (NULL);
	burnout_list_action(MV_BACK, self);
	while (sim_action(STAT, NULL) == ON)
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++](self);
	}
	if (SIM_DEBUG) puts("[event loop]: simulatoin no longer going, leaving...");
	return (NULL);
}
