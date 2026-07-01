/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/01 18:40:07 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../parser/parser.h"

typedef void		(*t_routines)(t_coder *);

typedef struct s_monitor
{
	pthread_t		thread;
	pthread_t		*coders_threads;
	pthread_cond_t	*monitor_router;
	int				coder_thread_init_ok;
	int				cond_init_ok;
	t_coder			**coders_burnout_heap;
	t_sim			*sim;

	pthread_mutex_t	target_compile_mutex;
	bool			target_compiled;

}					t_monitor;

typedef struct s_sim
{
	t_monitor		monitor;
	t_dongle		*dongles;
	t_coder			*coders;

	t_params		params;
	t_timeval		startup;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	running_mutex;

	pthread_cond_t	birth_control;
	t_routines		routines[3];

	bool			running;
}					t_sim;

int					init_simulation(t_sim *sim, char **argv);
void				*monitor(void *t_sim_p);


#endif
