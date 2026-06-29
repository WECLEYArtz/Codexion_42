/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 17:16:17 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "../dependencies.h"
#include "../dongle/dongle.h"
#include "../parser/parser.h"
#include "../simulation/simulation.h"

// NOTE: The only thing this lacks now is taking the dongle, maybe more...
void	compile(t_coder *coder)
{
	// coder->dongle_l->request(coder->id);
	announce(coder, "has taken a dongle");
	announce(coder, "is compiling");
	usleep(coder->sim->params.time_to_compile * 1000);
}

void	debug(t_coder *coder)
{
	announce(coder, "is debuging");
	usleep(coder->sim->params.time_to_debug * 1000);
}

void	refactor(t_coder *coder)
{
	announce(coder, "is refactoring");
	usleep(coder->sim->params.time_to_refactor * 1000);
}

void	announce(t_coder *coder, char *action)
{
	t_timeval	current;

	gettimeofday(&current, NULL); // search what goes instead of Null
	pthread_mutex_lock(&coder->sim->print_mutex);
	printf("%ld %d %s\n", (current.tv_sec * 1000 + current.tv_usec / 1000)
		- (coder->sim->startup.tv_sec * 1000 + coder->sim->startup.tv_usec
			/ 1000), coder->id, action);
	pthread_mutex_unlock(&coder->sim->print_mutex);
}
