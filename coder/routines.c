/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 20:14:31 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dongle/dongle.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

void	compile(t_coder *coder)
{
	t_timespec	abstime;

	if (try_take_dongles(coder->dongle_r, coder->dongle_l, coder) == END)
		return ;
	pthread_mutex_lock(&coder->compiled_mutex);
	announce(coder, ANNOUCE_COMPILE, false);
	coder_compiled_status_update(coder);
	pthread_cond_signal(coder->monitor_link);
	burnout_list_action(MV_BACK, coder);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
	pthread_mutex_unlock(&coder->compiled_mutex);
	if (sim_action(WAIT_STP, &abstime) == END)
		return ;
	untake_dongle(coder->dongle_r, coder);
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
