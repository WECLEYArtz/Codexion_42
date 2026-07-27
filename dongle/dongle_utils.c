/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 02:42:03 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

// NOTE:	if we insert everytime we dont find the requester coder,
// 			what are the odds of soemthing to go wrong? like duplication.

static int	safe_wait_dongle(t_dongle *d_to_waited, t_dongle *d_to_released,
		t_coder *cdr)
{

	if (sim_action(STAT, NULL) == END)
	{
		pthread_mutex_unlock(&d_to_waited->mutex);
		pthread_mutex_unlock(&d_to_released->mutex);
		return 1;
	}
	if (d_to_waited->heap[0] == cdr && d_to_waited->taken == false)
		return 0;
	pthread_mutex_unlock(&d_to_released->mutex);
	pthread_cond_wait(&d_to_waited->cond, &d_to_waited->mutex);
	pthread_mutex_lock(&d_to_released->mutex);
	return 0;
}

int	try_take_dongles(t_dongle *dngl_r, t_dongle *dngl_l, t_coder *cdr)
{
	pthread_mutex_lock(&dngl_r->mutex);
	pthread_mutex_lock(&dngl_l->mutex);

	if (HEAP_DEBUG) __debug_heap__(dngl_r, cdr, "inserting to a dongle_r...");

	dhq_insert(dngl_r, cdr);

	if (HEAP_DEBUG) __debug_heap__(dngl_r, cdr, "inserted to a dongle_r");


	if (HEAP_DEBUG) __debug_heap__(dngl_l, cdr, "inserting to a dongle_l...");

	dhq_insert(dngl_l, cdr);

	if (HEAP_DEBUG) __debug_heap__(dngl_l, cdr, "inserted to a dongle_l");



	while ((dngl_r->heap[0] != cdr || dngl_r->taken ||
				dngl_l->heap[0] != cdr || dngl_l->taken))
	{
		if (HEAP_DEBUG) __debug_heap__(dngl_r, cdr, "sleeping on dongle_r");

		if (safe_wait_dongle(dngl_r, dngl_l, cdr))
			return (1);

		if (HEAP_DEBUG) __debug_heap__(dngl_r, cdr, "sleeping on dongle_l");

		if (safe_wait_dongle(dngl_l, dngl_r, cdr))
			return (1);
	}

	if (HEAP_DEBUG) __debug_heap__(dngl_r, cdr, "waiting until dongles available (d_r)");

	if (sim_action(WAIT_STP, &dngl_r->available_date) == END
			|| sim_action(WAIT_STP, &dngl_l->available_date) == END)
		return 1;
	dngl_r->taken = true;
	dngl_l->taken = true;

	if (HEAP_DEBUG) __debug_heap__(dngl_r, cdr, GREEN"Dongles_r taken!"RESET);
	if (HEAP_DEBUG) __debug_heap__(dngl_l, cdr, GREEN"Dongles_l taken!"RESET);

	pthread_mutex_unlock(&dngl_l->mutex);
	pthread_mutex_unlock(&dngl_r->mutex);
	return (0);
}

void	untake_dongle(t_dongle *dongle, t_coder *coder)
{
	t_timespec	new;

	pthread_mutex_lock(&dongle->mutex);
	clock_gettime(CLOCK_REALTIME, &dongle->available_date);

	if (HEAP_DEBUG) __debug_heap__(dongle, coder, "untaking a dongle...");

	new = get_abstime(&dongle->available_date,
			&dongle->sim->ta_dongle_cooldown);
	dongle->available_date = new;



	if (HEAP_DEBUG) __debug_heap__(dongle, coder, "popping off from a dongle...");

	dhq_pop(dongle);

	if (HEAP_DEBUG) __debug_heap__(dongle, coder, "poped off from a dongle");




	dongle->taken = false;


	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
	if (HEAP_DEBUG) __debug_heap__(dongle, coder, "untaken a dongle");
}
