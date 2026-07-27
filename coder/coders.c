/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 02:40:05 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"


static	int	first_compile(t_coder *coder)
{
	static pthread_mutex_t	first_compile_mutex = PTHREAD_MUTEX_INITIALIZER;
	static bool				first_compile_taken = false;

	pthread_mutex_lock(&first_compile_mutex);
	if (!first_compile_taken)
	{
		coder->first_compiler = true;
		first_compile_taken = true;
	}
	else
	{
		pthread_mutex_unlock(&first_compile_mutex);
		return (0);
	}
	pthread_mutex_unlock(&first_compile_mutex);
	return (1);
}

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

//	Responsible for updating last compile and burnout date.
//	First called when the coder is created, then everytime a coder compiles.
void	coder_dates_update(t_coder *coder)
{
	clock_gettime(CLOCK_REALTIME, &coder->last_compile);
	coder->burnout_date = get_abstime(
			&coder->last_compile,
			&coder->sim->ta_burnout);
}
