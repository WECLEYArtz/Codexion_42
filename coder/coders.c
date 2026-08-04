/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"

//	Responsible for updating last compile and burnout date.
//	First called when the coder is created, then everytime a coder compiles.

// NOTE: if you can find a way to make sim accessible easielly 
void	coder_compiled_status_update(t_coder *coder)
{
	t_sim	*sim;

	sim = coder->sim;
	clock_gettime(CLOCK_REALTIME, &coder->last_compile);
	coder->burnout_date = get_abstime(
			&coder->last_compile,
			&coder->sim->ta_burnout);
	coder->compiles_required--;
	if (coder->compiles_required == 0)
	{
		pthread_mutex_lock(&sim->unfinished_coders_mutex);
		sim->unfinished_coders--;
		pthread_mutex_unlock(&sim->unfinished_coders_mutex);
	}
}

void	*coder_routine(void *coder_p)
{
	static short	(*routines[3])(t_coder *) = {compile, debug, refactor};
	int				routine_turn;
	t_coder			*self;

	routine_turn = 0;
	self = (t_coder *)coder_p;
	if (sim_action(WAIT_RUN, NULL) == END || self->compiles_required == 0)
		return (NULL);
	burnout_list_action(MV_BACK, self);
	while (1)
	{
		if (routine_turn == 3)
			routine_turn = 0;
		if (routines[routine_turn++](self) == END)
			break ;
	}
	return (NULL);
}

void	*single_coder_routine(void *coder_p)
{
	t_coder		*self;

	self = (t_coder *)coder_p;
	if (sim_action(WAIT_RUN, NULL) == END || self->compiles_required == 0)
		return (NULL);
	burnout_list_action(MV_BACK, self);
	dhq_insert(self->dongle_r, self);
	single_announce(self);
	return (NULL);
}
