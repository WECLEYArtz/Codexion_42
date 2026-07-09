/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/09 13:53:59 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../parser/parser.h"
#include "../simulation/simulation.h"

// NOTE: The only thing this lacks now is taking the dongle, maybe more...

// NOTE: The order of locking -> unlocking -> broadcasting is suspecious
void	compile(t_coder *coder)
{
	// coder->dongle_l->request(coder->id);
	announce(coder, "has taken a dongle");
	gettimeofday(&coder->last_compile, NULL);
	pthread_cond_broadcast(coder->monitor_link);
	announce(coder, "is compiling");
	usleep(coder->sim->args.time_to_compile * 1000);

	pthread_mutex_lock(&coder->compiled_mutex);
	coder->compiled++;
	burnoutpq_mvback(&coder->burnout_node);
	pthread_mutex_unlock(&coder->compiled_mutex);
	pthread_cond_broadcast(coder->monitor_link);
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
	t_timeval		current;
	static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;

	gettimeofday(&current, NULL); // search what goes instead of Null
	pthread_mutex_lock(&print_mutex);
	printf("%ld %d %s\n", (current.tv_sec * 1000 + current.tv_usec / 1000)
		- (coder->sim->startup.tv_sec * 1000 + coder->sim->startup.tv_usec
			/ 1000), coder->id, action);
	pthread_mutex_unlock(&print_mutex);
}
