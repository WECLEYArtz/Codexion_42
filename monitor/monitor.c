/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 16:17:57 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

// NOTE:	recheck	the condition in a clearer way
static int	wait_coder_burnout(t_coder *coder)
{
	t_timespec	burnout_date;
	int			old_compiles_count;
	int			rc;

	pthread_mutex_lock(&coder->compiled_mutex);
	old_compiles_count = coder->compiles_required;
	burnout_date = coder->burnout_date;
	while (1)
	{
		rc = pthread_cond_timedwait(coder->monitor_link, &coder->compiled_mutex,
				&burnout_date);
		if (!rc && old_compiles_count == coder->compiles_required)
			continue ;
		if (rc && old_compiles_count == coder->compiles_required)
		{
			pthread_mutex_unlock(&coder->compiled_mutex);
			sim_action(END, NULL);
			return (announce(coder, ANNOUCE_BURNOUT, true), 1);
		}
		pthread_mutex_unlock(&coder->compiled_mutex);
		pthread_mutex_lock(&coder->sim->unfinished_coders_mutex);
		if (coder->sim->unfinished_coders == 0)
			return (sim_action(END, NULL), 1);
		pthread_mutex_unlock(&coder->sim->unfinished_coders_mutex);
		return (0);
	}
}

void	*monitor_routine(void *unused)
{
	(void)unused;
	burnout_list_action(M_WATCH, NULL);
	while (!wait_coder_burnout(burnout_list_action(POP, NULL)))
		;
	return (NULL);
}
