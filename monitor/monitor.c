/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 17:18:14 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../monitor/monitor.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"

static int	wait_coder_burnout(t_coder *coder, t_time_add *ta_burnout)
{
	int			old_compiles;
	int			rc;
	t_timespec	abstime;

	pthread_mutex_lock(&coder->compiled_mutex);
	old_compiles = coder->compiled;
	abstime = get_abstime(&coder->last_compile, ta_burnout);
	while (1)
	{
		rc = pthread_cond_timedwait(coder->monitor_link, &coder->compiled_mutex,
				&abstime);
		if (!rc && old_compiles == coder->compiled)
			continue ;
		else if (rc && old_compiles == coder->compiled)
		{
			pthread_mutex_unlock(&coder->compiled_mutex);
			sim_action(END, NULL);
			return (announce(coder, ANNOUCE_BURNOUT, true), 1);
		}
		else
			return (pthread_mutex_unlock(&coder->compiled_mutex), 0);
	}
}

void	*monitor_routine(void *t_sim_p)
{
	t_monitor	*monitor;
	t_time_add	*burnout_ta;

	burnout_ta = &((t_sim *)t_sim_p)->ta_burnout;
	monitor = ((t_sim *)t_sim_p)->monitor;
	burnout_list_action(M_WATCH, monitor);
	while (!wait_coder_burnout(burnout_list_action(POP, NULL), burnout_ta))
		;
	return (NULL);
}
