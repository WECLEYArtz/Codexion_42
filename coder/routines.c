/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/27 19:42:54 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../parser/parser.h"
#include "../simulation/simulation.h"

// NOTE: The only thing this lacks now is taking the dongle
void	compile(t_coder *coder)
{
	// coder->dongle_l->request(coder->id);
	announce(coder, "compiling");
	sleep(coder->sim->params.time_to_compile);
}

void	debug(t_coder *coder)
{
	announce(coder, "debuging");
	sleep(coder->sim->params.time_to_debug);
}

void	refactor(t_coder *coder)
{
	announce(coder, "refactoring");
	sleep(coder->sim->params.time_to_refactor);
}

void	announce(t_coder *coder, char *action)
{
	t_timeval	current;

	gettimeofday(&current, NULL); // search what goes instead of Null
	pthread_mutex_lock(&coder->sim->print_mutex);
	printf("%d %d is %s\n",
			(int)(current.tv_sec - coder->sim->startup.tv_sec) * 100,
		coder->id, action);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}
