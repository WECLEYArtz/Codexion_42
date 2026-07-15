/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 01:57:41 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../parser/parser.h"
#include "../simulation/simulation.h"

// NOTE: The only thing this lacks now is taking the dongle, maybe more...
static void	_compile_work(t_coder *coder)
{
	// coder->dongle_l->request(coder->id);
	announce(coder, "has taken a dongle", 0);
	gettimeofday(&coder->last_compile, NULL);
	announce(coder, "is compiling", 0);
	// if (DEBUG) announce(coder, RED "[debug] Locking mutex CMPL" RESET);
	pthread_mutex_lock(&coder->compiled_mutex);
	coder->compiled++;
	pthread_mutex_unlock(&coder->compiled_mutex);
	// if (DEBUG) announce(coder, GREEN "[debug] Unlocking mutex CMPL" RESET);
	burnoutpq_mvback(&coder->burnout_node);
}

int		first_compile(t_coder *coder)
{
	static pthread_mutex_t	first_compile_mutex = PTHREAD_MUTEX_INITIALIZER;
	static bool				first_compile_taken = false;

	pthread_mutex_lock(&first_compile_mutex);
	if (!first_compile_taken)
		first_compile_taken = true;
	else
	{
		pthread_mutex_unlock(&first_compile_mutex);
		return(0) ;
	}
	pthread_mutex_unlock(&first_compile_mutex);
	if (sim_get_status())
	{
		_compile_work(coder);

		burnoutpq_monitor_gwake(&coder->sim->monitor.general_cond);

		sim_routine_wait(get_abstime(&coder->last_compile,	&coder->sim->ta_compile));
	}
	return(1);
}

void	compile(t_coder *coder)
{
	_compile_work(coder);
	pthread_mutex_lock(&coder->compiled_mutex);
	pthread_cond_signal(coder->monitor_link);
	pthread_mutex_unlock(&coder->compiled_mutex);
	if (sim_get_status() == false)
		return;
	usleep(coder->sim->args.time_to_compile * 1000);
	sim_routine_wait(get_abstime(&coder->last_compile,	&coder->sim->ta_compile));
}

void	debug(t_coder *coder)
{
	announce(coder, "is debuging", 0);
	sim_routine_wait(get_abstime(&coder->last_compile,	&coder->sim->ta_debug));
}

void	refactor(t_coder *coder)
{
	announce(coder, "is refactoring", 0);
	sim_routine_wait(get_abstime(&coder->last_compile,	&coder->sim->ta_refactor));
}

