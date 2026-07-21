/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 17:10:43 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../parser/parser.h"

# define OFF 0
# define ON 1
# define END 2
# define STAT 3
# define WAIT_RUN 4
# define WAIT_STP 5

typedef struct s_time_add
{
	long			sec;
	long			nsec;
}					t_time_add;

typedef struct s_init_records
{
	int				c_thread_init_ok;
	int				c_mutex_init_ok;
	int				m_cond_init_ok;
	int				d_mutex_init_ok;
	int				d_cond_init_ok;
}					t_init_records;

typedef struct s_sim
{
	t_dongle		*dongles;
	t_coder			*coders;
	t_monitor		*monitor;

	t_time_add		ta_burnout;
	t_time_add		ta_compile;
	t_time_add		ta_debug;
	t_time_add		ta_refactor;

	t_args			args;

	t_timespec		startup;

	t_init_records	init_records;
}					t_sim;

int					init_simulation(t_sim *sim, t_monitor *monitor,
						char **argv);
short				sim_action(short choice, t_timespec *abstime);
void				preseed_dongles_heap(t_sim *sim);

void				_init_sim_ta(t_sim *sim);
int					_create_coder(t_coder *coder, int order, t_sim *sim);

#endif
