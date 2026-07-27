/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 16:16:29 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"


// NOTE: looks clumsy as shit, probably causes burnout
void	compile(t_coder *coder)
{
	t_timespec				abstime;

	if (try_take_dongles(coder->dongle_r, coder->dongle_l, coder) == END)
		return;
	pthread_mutex_lock(&coder->compiled_mutex);

	pthread_cond_signal(coder->monitor_link);
	announce(coder, ANNOUCE_COMPILE, false);
	coder_compiled_status_update(coder);
	burnout_list_action(MV_BACK, coder);
	if (sim_action(STAT, NULL) != ON)
		return ;
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
	sim_action(WAIT_STP, &abstime);

	pthread_mutex_unlock(&coder->compiled_mutex);

	__debug_heap__(coder->dongle_r, coder, "dropping dongle_r");
	untake_dongle(coder->dongle_r, coder);

	__debug_heap__(coder->dongle_l, coder, "dropping dongle_l");
	untake_dongle(coder->dongle_l, coder);
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
