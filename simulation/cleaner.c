/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 14:31:29 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simulation/simulation.h"

void sim_cleaner(t_sim *sim)
{
	free(sim->dongles);
	free(sim->coders);
	pthread_mutex_destroy(&sim->birth_mutex);
	pthread_mutex_destroy(&sim->running_mutex);
	pthread_mutex_destroy(&sim->birth_mutex);
}
