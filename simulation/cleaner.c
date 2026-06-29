/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 17:16:17 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simulation/simulation.h"

void	simcleaner(t_sim *sim, int step)
{
	free(sim->dongles);
	free(sim->coders);
	if (step >= 1)
		pthread_mutex_destroy(&sim->running_mutex);
	if (step >= 2)
		pthread_mutex_destroy(&sim->print_mutex);
	if (step >= 3)
		pthread_cond_destroy(&sim->birth_control);
}
