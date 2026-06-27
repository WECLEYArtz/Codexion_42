/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 14:29:38 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/27 18:37:25 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../simulation/simulation.h"
#include <pthread.h>

void sim_cleaner(t_sim *sim)
{
	free(sim->dongles);
	free(sim->coders);
	pthread_mutex_destroy(&sim->print_mutex);
	pthread_mutex_destroy(&sim->running_mutex);
	pthread_cond_destroy(&sim->birth_control);
}
