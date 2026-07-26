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
#include "../dongle/dongle.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

// NOTE:	if we insert everytime we dont find the requester coder,
// 			what are the odds of soemthing to go wrong? like duplication.

void	safe_wait_dongle(t_dongle *dong_to_waited, t_dongle *dong_to_released)
{
	if (!dong_to_waited->taken)
		return ;
	pthread_mutex_unlock(&dong_to_released->mutex);
	pthread_cond_wait(&dong_to_waited->cond, &dong_to_waited->mutex);
	pthread_mutex_lock(&dong_to_released->mutex);
}

void	try_take_dongles(t_dongle *dngl_r, t_dongle *dngl_l, t_coder *cdr)
{
	pthread_mutex_lock(&dngl_r->mutex);
	pthread_mutex_lock(&dngl_l->mutex);
	dhq_insert(dngl_r, cdr);
	dhq_insert(dngl_r, cdr);
	while (dngl_l->heap[0] != cdr || dngl_r->heap[0] != cdr ||
			dngl_l->taken || dngl_r->taken)
	{
		safe_wait_dongle(dngl_r, dngl_l);
		safe_wait_dongle(dngl_l, dngl_r);
	}
	sim_action(WAIT_STP, &dngl_l->available_date);
	sim_action(WAIT_STP, &dngl_r->available_date);
	dngl_l->taken = true;
	dngl_r->taken = true;
	pthread_mutex_unlock(&dngl_l->mutex);
	pthread_mutex_unlock(&dngl_r->mutex);
}

void	unequip(t_dongle *dongle, t_coder *coder)
{
	t_timespec	new;

	pthread_mutex_lock(&dongle->mutex);
	clock_gettime(CLOCK_REALTIME, &dongle->available_date);
	new = get_abstime(&dongle->available_date,
			&dongle->sim->ta_dongle_cooldown);
	dongle->available_date = new;
	dhq_pop(dongle);
	dongle->taken = false;
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
