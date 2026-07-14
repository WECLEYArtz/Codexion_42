/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/14 03:37:04 by ahmounsi         ###   ########.fr       */
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
	announce(coder, "has taken a dongle");
	gettimeofday(&coder->last_compile, NULL);
	announce(coder, "is compiling");
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
	_compile_work(coder);

	burnoutpq_monitor_gwake(&coder->sim->monitor.general_cond);

	usleep(coder->sim->args.time_to_compile * 1000);
	return(1);
}

void	compile(t_coder *coder)
{
	_compile_work(coder);
	pthread_mutex_lock(&coder->compiled_mutex);
	pthread_cond_broadcast(coder->monitor_link);
	pthread_mutex_unlock(&coder->compiled_mutex);
	usleep(coder->sim->args.time_to_compile * 1000);
}

void	debug(t_coder *coder)
{
	announce(coder, "is debuging");
	usleep(coder->sim->args.time_to_debug * 1000);
}

void	refactor(t_coder *coder)
{
	announce(coder, "is refactoring");
	usleep(coder->sim->args.time_to_refactor * 1000);
}

void	announce(t_coder *coder, char *action)
{
	t_timeval				current;
	static pthread_mutex_t	print_mutex = PTHREAD_MUTEX_INITIALIZER;

	gettimeofday(&current, NULL);
	pthread_mutex_lock(&print_mutex);
	printf("%ld %d %s\n", (current.tv_sec * 1000 + current.tv_usec / 1000)
		- (coder->sim->startup.tv_sec * 1000 + coder->sim->startup.tv_usec
			/ 1000), coder->id, action);
	pthread_mutex_unlock(&print_mutex);
}
