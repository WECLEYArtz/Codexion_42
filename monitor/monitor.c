/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/29 16:12:53 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../monitor/monitor.h"
#include "../simulation/simulation.h"
#include "../utils/utils.h"

// NOTE:	recheck	the condition in a clearer way
static int	wait_coder_burnout(t_coder *coder)
{
	int			old_compiles;
	t_timespec	burnout_date;
	int			rc;

	pthread_mutex_lock(&coder->compiled_mutex);
	old_compiles = coder->compiled;
	burnout_date = coder->burnout_date;
	while (1)
	{
		rc = pthread_cond_timedwait(coder->monitor_link, &coder->compiled_mutex,
				&burnout_date);
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
void	*monitor_routine(void *unused)
{
	(void)unused;
	burnout_list_action(M_WATCH, NULL);
	while (!wait_coder_burnout(burnout_list_action(POP, NULL)))
		;
	return (NULL);
}
