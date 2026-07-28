/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 19:50:40 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

//	a mini locking function that help resolve lock order violation

// PERF: optimise performance, dereference once when passing to function
//			swap values in if condition
static void _lock_dongles(t_dongle *dngl_1, t_dongle *dngl_2)
{
	if (&dngl_1->mutex < &dngl_2->mutex)
	{
		pthread_mutex_lock(&dngl_1->mutex);
		pthread_mutex_lock(&dngl_2->mutex);
	}
	else
	{
		pthread_mutex_lock(&dngl_2->mutex);
		pthread_mutex_lock(&dngl_1->mutex);
	}
}

//	a mini locking function that help resolve lock order violation
static void _unlock_dongles(t_dongle *dngl_1, t_dongle *dngl_2)
{
	if (&dngl_1->mutex < &dngl_2->mutex)
	{
		pthread_mutex_unlock(&dngl_2->mutex);
		pthread_mutex_unlock(&dngl_1->mutex);
	}
	else
	{
		pthread_mutex_unlock(&dngl_1->mutex);
		pthread_mutex_unlock(&dngl_2->mutex);
	}
}

// PERF:	the way this lock mess happens looks performance concerning.
// 			try to fix later
static int	safe_wait_dongle(t_dongle *dngl_r, t_dongle *dngl_l,
		t_dongle *d_target, t_coder *cdr)
{
	if (sim_action(STAT, NULL) == END)
	{
		//__debug_heap__(dngl_r, cdr, "sleeping skipped, simulation ends");
		return END;
	}
	_unlock_dongles(dngl_r, dngl_l);
	pthread_mutex_lock(&d_target->mutex);
	while(d_target->heap[0] != cdr && d_target->taken == true)
		pthread_cond_wait(&d_target->cond, &d_target->mutex);
	pthread_mutex_unlock(&d_target->mutex);
	_lock_dongles(dngl_r, dngl_l);
	return 0;
}

int	try_take_dongles(t_dongle *dngl_r, t_dongle *dngl_l, t_coder *cdr)
{
	_lock_dongles(dngl_r, dngl_l);
	//__debug_heap__(dngl_r, cdr, "inserting to a dongle_r...");
	dhq_insert(dngl_r, cdr);
	//__debug_heap__(dngl_r, cdr, "inserted to a dongle_r");
	//__debug_heap__(dngl_l, cdr, "inserting to a dongle_l...");
	dhq_insert(dngl_l, cdr);
	//__debug_heap__(dngl_l, cdr, "inserted to a dongle_l");
	while ((dngl_r->heap[0] != cdr || dngl_r->taken ||
				dngl_l->heap[0] != cdr || dngl_l->taken))
	{
		//__debug_heap__(dngl_r, cdr, "sleeping on dongle_r");
		if (safe_wait_dongle(dngl_r, dngl_l, dngl_r, cdr) == END)
			return ( _unlock_dongles(dngl_r, dngl_l), END);
		//__debug_heap__(dngl_r, cdr, "sleeping on dongle_l");
		if (safe_wait_dongle(dngl_r, dngl_l, dngl_l, cdr) == END)
			return (_unlock_dongles(dngl_r, dngl_l), END);
	}
	_unlock_dongles(dngl_r, dngl_l);

	//__debug_heap__(dngl_r, cdr, "waiting until dongles available (d_r)");
	if (sim_action(WAIT_STP, &dngl_r->available_date) == END
			|| sim_action(WAIT_STP, &dngl_l->available_date) == END)
		return (1);

	_lock_dongles(dngl_r, dngl_l);
	dngl_r->taken = true;
	dngl_l->taken = true;
	_unlock_dongles(dngl_r, dngl_l);
	return (0);
}

void	untake_dongle(t_dongle *dongle, t_coder *coder)
{
	t_timespec	new;

	if (!coder)
		coder = NULL;// error suspender
	pthread_mutex_lock(&dongle->mutex);
	//__debug_heap__(dongle, coder, "untaking a dongle... (mutex check)");
	clock_gettime(CLOCK_REALTIME, &dongle->available_date);
	new = get_abstime(&dongle->available_date,
			&dongle->sim->ta_dongle_cooldown);
	dongle->available_date = new;
	//__debug_heap__(dongle, coder, "popping off from a dongle...");
	dhq_pop(dongle, coder);
	//__debug_heap__(dongle, coder, "poped off from a dongle");
	dongle->taken = false;
	pthread_cond_signal(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
	//__debug_heap__(dongle, coder, BLUE"untaken a dongle"RESET);
}
