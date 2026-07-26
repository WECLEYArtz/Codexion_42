/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/26 13:37:05 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"
#include "../dongle/dongle.h"

// NOTE:	if we insert everytime we dont find the requester coder,
// 			what are the odds of soemthing to go wrong? like duplication.

void	request(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);

	__debug_heap__(dongle, coder, "Entered request proccess");//debug
	if (dongle->heap[0] != coder)
		dhq_insert(dongle, coder);
	while (dongle->heap[0] != coder || dongle->taken)
	{
		__debug_heap__(dongle, coder, "Sleeping");//debug
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
		__debug_heap__(dongle, coder, "Got awaken");//debug
	}
	__debug_heap__(dongle, coder, "Waiting cooldown...");//debug
	sim_action(WAIT_STP, &dongle->available_date);
	dongle->taken = true;
	__debug_heap__(dongle, coder, GREEN"Took dongle"RESET);//debug
	pthread_mutex_unlock(&dongle->mutex);
}

void	unequip(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	clock_gettime(CLOCK_REALTIME, &dongle->available_date);
	dongle->available_date = get_abstime(
			&dongle->available_date, 
			&dongle->sim->ta_dongle_cooldown);
	__debug_heap__(dongle, coder, YELLOW"Popeding..."RESET);//debug
	dhq_pop(dongle);
	dongle->taken = false;

	__debug_heap__(dongle, coder, YELLOW"Popod, Signaling..."RESET);//debug
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
