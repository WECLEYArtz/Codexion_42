/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_preseeders.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:48:08 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"
#include "simulation.h"

void	preseed_dongles_heap(t_sim *sim)
{
	int		i;
	int		coders_count;
	t_coder	*coder;
	short	priority_order;

	priority_order = 0;
	coders_count = sim->args.number_of_coders;
	coder = sim->coders;
	i = 1;
	while (priority_order < 2)
	{
		while (i < coders_count)
		{
			(coder + i)->dongle_r->heap[priority_order] = coder + i;
			(coder + i)->dongle_l->heap[priority_order] = coder + i;
			i += 2;
		}
		i = 0 + 2 * (coders_count > 2 && coders_count % 2);
		priority_order++;
	}
	if (coders_count > 2 && coders_count % 2)
	{
		(coder)->dongle_r->heap[0] = coder;
		(coder)->dongle_l->heap[1] = coder;
	}
}

void	preseed_coders_firstcompile(t_sim *sim)
{
	int		i;
	int		coders_count;
	t_coder	*coder;

	i = 1;
	coders_count = sim->args.number_of_coders;
	coder = sim->coders;
	while (i < coders_count)
	{
		coder_compiled_status_update(coder + i);
		i += 2;
	}
	i = 0;
	while (i < coders_count)
	{
		coder_compiled_status_update(coder + i);
		i += 2;
	}
}
