/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 16:06:34 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../monitor/monitor.h"
#include "../utils/utils.h"
#include "../simulation/simulation.h"

// NOTE:	recheck	the condition in a clearer way
static int	wait_coder_burnout(t_coder *coder)
{
	int			old_compiles;
	int			rc;

	pthread_mutex_lock(&coder->compiled_mutex);
	old_compiles = coder->compiled;
	while (1)
	{
		rc = pthread_cond_timedwait(coder->monitor_link, &coder->compiled_mutex,
				&coder->burnout_date);
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

// PERF:	just copy ta_burnout for locality and performance
void	*monitor_routine(void *t_sim_p)
{
	t_monitor	*monitor;

	monitor = ((t_sim *)t_sim_p)->monitor;
	if (SIM_DEBUG) puts(YELLOW"[MONITOR]: waiting AWAKEN"RESET);
	burnout_list_action(M_WATCH, monitor);
	if (SIM_DEBUG) puts(YELLOW"[MONITOR]: AWAKEN"RESET);
	while (!wait_coder_burnout(burnout_list_action(POP, NULL)))
		;
	return (NULL);
}
