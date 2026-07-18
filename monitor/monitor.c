/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/18 13:38:13 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../simulation/simulation.h"

static int	wait_coder_burnout(t_coder *coder, t_timeadd *ta_burnout)
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
			sim_action(OFF, NULL);
			return (announce(coder, RED "has burnouted" RESET, 1), 1);
		}
		else
			return (pthread_mutex_unlock(&coder->compiled_mutex), 0);
	}
}

void	*monitor(void *t_sim_p)
{
	t_monitor	*monitor;
	t_timeadd	*burnout_ta;

	burnout_ta = &((t_sim *)t_sim_p)->ta_burnout;
	monitor = &((t_sim *)t_sim_p)->monitor;
	burnoutpq_action(MWATCH, monitor);
	while (!wait_coder_burnout(burnoutpq_action(POP, NULL), burnout_ta))
		;
	return (NULL);
}
