/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/25 18:49:16 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

static void	_compile_work(t_coder *coder)
{
	__debug_heap__(coder->dongle_r, coder, "Request dongle_r");
	request(coder->dongle_r, coder);

	__debug_heap__(coder->dongle_l, coder, "Request dongle_l");
	request(coder->dongle_l, coder);


	announce(coder, ANNOUCE_COMPILE, false);
	pthread_mutex_lock(&coder->compiled_mutex);
	coder_dates_update(coder);
	coder->compiled++;
	pthread_mutex_unlock(&coder->compiled_mutex);
	burnout_list_action(MV_BACK, coder);


}

int	first_compile(t_coder *coder)
{
	static pthread_mutex_t	first_compile_mutex = PTHREAD_MUTEX_INITIALIZER;
	static bool				first_compile_taken = false;
	t_timespec				abstime;

	pthread_mutex_lock(&first_compile_mutex);
	if (!first_compile_taken)
		first_compile_taken = true;
	else
	{
		pthread_mutex_unlock(&first_compile_mutex);
		return (0);
	}
	pthread_mutex_unlock(&first_compile_mutex);
	if (sim_action(STAT, NULL) == ON)
	{
		_compile_work(coder);
		pthread_mutex_lock(&coder->compiled_mutex);
		abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
		pthread_mutex_unlock(&coder->compiled_mutex);
		burnout_list_action(M_WAKE, NULL);
		sim_action(WAIT_STP, &abstime);

		__debug_heap__(coder->dongle_l, coder, "Unequiping dongle_l");
		unequip(coder->dongle_l, coder);

		__debug_heap__(coder->dongle_r, coder, "Unequiping dongle_r");
		unequip(coder->dongle_r, coder);
	}
	puts(RED"First compile END"RESET);
	return (1);
}

void	compile(t_coder *coder)
{
	t_timespec	abstime;

	_compile_work(coder);
	pthread_mutex_lock(&coder->compiled_mutex);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
	pthread_cond_signal(coder->monitor_link);
	pthread_mutex_unlock(&coder->compiled_mutex);
	if (sim_action(STAT, NULL) == OFF)
		return ;
	sim_action(WAIT_STP, &abstime);

	__debug_heap__(coder->dongle_l, coder, "Unequiping dongle_l");
	unequip(coder->dongle_l, coder);

	__debug_heap__(coder->dongle_r, coder, "Unequiping dongle_r");
	unequip(coder->dongle_r, coder);
}

void	debug(t_coder *coder)
{
	t_timespec	abstime;

	announce(coder, ANNOUCE_DEBUG, false);
	pthread_mutex_lock(&coder->compiled_mutex);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_debug);
	pthread_mutex_unlock(&coder->compiled_mutex);
	sim_action(WAIT_STP, &abstime);
}

void	refactor(t_coder *coder)
{
	t_timespec	abstime;

	announce(coder, ANNOUCE_REFACTOR, false);
	pthread_mutex_lock(&coder->compiled_mutex);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_refactor);
	pthread_mutex_unlock(&coder->compiled_mutex);
	sim_action(WAIT_STP, &abstime);
}
