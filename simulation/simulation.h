/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/07 14:11:16 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../parser/parser.h"

typedef struct s_monitor
{
	pthread_t		thread;
	pthread_t		*coders_threads;
	pthread_cond_t	*monitor_router;
	int				coder_thread_init_ok;
	int				cond_init_ok;
	// t_coder			**coders_burnout_heap; (replace with linked list)
}					t_monitor;

typedef struct s_sim
{
	t_monitor		monitor;
	t_dongle		*dongles;
	t_coder			*coders;

	t_args			args;
	t_timeval		startup;
}					t_sim;

int					init_simulation(t_sim *sim, char **argv);
void				*monitor(void *t_sim_p);

#endif
