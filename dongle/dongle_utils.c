/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 20:16:26 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

static void	_lock_dongles(pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2)
{
	if (mutex_1 < mutex_2)
	{
		pthread_mutex_lock(mutex_1);
		pthread_mutex_lock(mutex_2);
	}
	else
	{
		pthread_mutex_lock(mutex_2);
		pthread_mutex_lock(mutex_1);
	}
}

static void	_unlock_dongles(pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2)
{
	if (mutex_1 < mutex_2)
	{
		pthread_mutex_unlock(mutex_2);
		pthread_mutex_unlock(mutex_1);
	}
	else
	{
		pthread_mutex_unlock(mutex_1);
		pthread_mutex_unlock(mutex_2);
	}
}

static int	safe_wait_dongle(t_dongle *d_target, t_coder *cdr)
{
	pthread_mutex_lock(&d_target->mutex);
	while (d_target->heap[0] != cdr || d_target->taken == true)
	{
		if (sim_action(STAT, NULL) == END)
			return (pthread_mutex_unlock(&d_target->mutex), END);
		pthread_cond_wait(&d_target->cond, &d_target->mutex);
	}
	pthread_mutex_unlock(&d_target->mutex);
	return (0);
}

int	try_take_dongles(t_dongle *dngl_r, t_dongle *dngl_l, t_coder *cdr)
{
	t_timespec	dngl_r_available;
	t_timespec	dngl_l_available;

	_lock_dongles(&dngl_r->mutex, &dngl_l->mutex);
	dhq_insert(dngl_r, cdr);
	dhq_insert(dngl_l, cdr);
	while ((dngl_r->heap[0] != cdr || dngl_r->taken
			|| dngl_l->heap[0] != cdr || dngl_l->taken))
	{
		_unlock_dongles(&dngl_r->mutex, &dngl_l->mutex);
		if (safe_wait_dongle(dngl_r, cdr) == END)
			return (END);
		if (safe_wait_dongle(dngl_l, cdr) == END)
			return (END);
		_lock_dongles(&dngl_r->mutex, &dngl_l->mutex);
	}
	dngl_r->taken = true;
	dngl_l->taken = true;
	dngl_r_available = dngl_r->available_date;
	dngl_l_available = dngl_l->available_date;
	_unlock_dongles(&dngl_r->mutex, &dngl_l->mutex);
	if (sim_action(WAIT_STP, &dngl_r_available) == END || sim_action(WAIT_STP,
			&dngl_l_available) == END)
		return (1);
	return (0);
}

void	untake_dongle(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	clock_gettime(CLOCK_REALTIME, &dongle->available_date);
	dongle->available_date = get_abstime(
			&dongle->available_date,
			&dongle->sim->ta_dongle_cooldown);
	dhq_pop(dongle, coder);
	dongle->taken = false;
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
