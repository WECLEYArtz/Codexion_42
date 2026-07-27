/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 03:30:15 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

void	compile(t_coder *coder)
{
	t_timespec				abstime;

	if (try_take_dongles(coder->dongle_r, coder->dongle_l, coder))
		return;
	announce(coder, ANNOUCE_COMPILE, false);
	pthread_mutex_lock(&coder->compiled_mutex);
	coder_dates_update(coder);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
	coder->compiled++;
	burnout_list_action(MV_BACK, coder);
	pthread_cond_signal(coder->monitor_link);
	if (coder->first_compiler)
	{
		if (SIM_DEBUG) puts(YELLOW"[Coder to monitor]: waking monitor"RESET);
		burnout_list_action(M_WAKE, NULL);
		coder->first_compiler = false;
		if (SIM_DEBUG) puts(YELLOW"[Coder to monitor]: First compile Granted"RESET);
	}
	else if (sim_action(STAT, NULL) == OFF)
		return ;
	sim_action(WAIT_STP, &abstime);
	pthread_mutex_unlock(&coder->compiled_mutex);

	__debug_heap__(coder->dongle_r, coder, "dropping dongle_r");
	untake_dongle(coder->dongle_r, coder);

	__debug_heap__(coder->dongle_l, coder, "dropping dongle_l");
	untake_dongle(coder->dongle_l, coder);
}

// PERF:	Optimise this, only use one compile function with flag

// PERF:	I dont think i need to check the simulation status
// 			when the monitor is not yet on that shuts it.
// 			the only reason it would be off is init cleanup, which would've been
// 			checked earlier than here.


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
