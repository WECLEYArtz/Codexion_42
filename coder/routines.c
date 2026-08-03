/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/03 02:44:47 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

short	compile(t_coder *coder)
{
	t_timespec	abstime;

	if (try_take_dongles(coder->dongle_r, coder->dongle_l, coder) == END)
		return (END);
	pthread_mutex_lock(&coder->compiled_mutex);
	announce(coder, ANNOUCE_COMPILE);
	coder_compiled_status_update(coder);
	burnout_list_action(MV_BACK, coder);
	pthread_cond_signal(coder->monitor_link);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
	pthread_mutex_unlock(&coder->compiled_mutex);
	if (sim_action(WAIT_STP, &abstime) == END)
		return (END);
	untake_dongle(coder->dongle_r, coder);
	untake_dongle(coder->dongle_l, coder);
	return (0);
}

short	debug(t_coder *coder)
{
	t_timespec	abstime;

	announce(coder, ANNOUCE_DEBUG);
	pthread_mutex_lock(&coder->compiled_mutex);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_debug);
	pthread_mutex_unlock(&coder->compiled_mutex);
	return (sim_action(WAIT_STP, &abstime));
}

short	refactor(t_coder *coder)
{
	t_timespec	abstime;

	announce(coder, ANNOUCE_REFACTOR);
	pthread_mutex_lock(&coder->compiled_mutex);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_refactor);
	pthread_mutex_unlock(&coder->compiled_mutex);
	return (sim_action(WAIT_STP, &abstime));
}
