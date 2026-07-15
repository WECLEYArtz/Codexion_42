/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 14:09:10 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

void	*coder_routine(void *coder_p)
{
	int		routine_turn;

	static void (*routines[3])(t_coder *) = {compile, debug, refactor};
	routine_turn = 0;
	sim_wait_run();
	if (sim_get_status() && first_compile((t_coder *)coder_p))
		routine_turn++;
	while (sim_get_status())
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++]((t_coder *)coder_p);
	}
	return (NULL);
}
