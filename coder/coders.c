/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/18 01:34:40 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../simulation/simulation.h"

void	*coder_routine(void *coder_p)
{
	static void	(*routines[3])(t_coder *) = {compile, debug, refactor};
	int			routine_turn;

	routine_turn = 0;
	if (!sim_action(STAT, NULL))
		if (!sim_action(WAITRUN, NULL))
			return (NULL);
	if (first_compile((t_coder *)coder_p))
		routine_turn++;
	while (sim_action(STAT, NULL))
	{
		if (routine_turn == 3)
			routine_turn = 0;
		routines[routine_turn++]((t_coder *)coder_p);
	}
	return (NULL);
}
