/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/18 01:43:45 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../simulation/simulation.h"

// NOTE: The only thing this lacks now is taking the dongle, maybe more...
// 			add takin dongle later...
static void	_compile_work(t_coder *coder)
{
	announce(coder, "has taken a dongle", 0);
	clock_gettime(CLOCK_REALTIME, &coder->last_compile);
	announce(coder, "is compiling", 0);
	pthread_mutex_lock(&coder->compiled_mutex);
	coder->compiled++;
	pthread_mutex_unlock(&coder->compiled_mutex);
	burnoutpq_action(MVBACK, coder);
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
	if (sim_action(STAT, NULL))
	{
		_compile_work(coder);
		abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
		burnoutpq_action(MWAKE, NULL);
		sim_action(WAITSTP, &abstime);
	}
	return (1);
}

void	compile(t_coder *coder)
{
	t_timespec	abstime;

	_compile_work(coder);
	pthread_mutex_lock(&coder->compiled_mutex);
	pthread_cond_signal(coder->monitor_link);
	pthread_mutex_unlock(&coder->compiled_mutex);
	if (sim_action(STAT, NULL) == false)
		return ;
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_compile);
	sim_action(WAITSTP, &abstime);
}

void	debug(t_coder *coder)
{
	t_timespec	abstime;

	announce(coder, "is debuging", 0);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_debug);
	sim_action(WAITSTP, &abstime);
}

void	refactor(t_coder *coder)
{
	t_timespec	abstime;

	announce(coder, "is refactoring", 0);
	abstime = get_abstime(&coder->last_compile, &coder->sim->ta_refactor);
	sim_action(WAITSTP, &abstime);
}
