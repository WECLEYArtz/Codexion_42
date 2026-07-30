/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 18:35:59 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../parser/parser.h"

# define SIM_DEBUG 0

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
	int				s_mutex_init_ok;
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
	t_time_add		ta_dongle_cooldown;

	pthread_mutex_t	unfinished_coders_mutex;
	int				unfinished_coders;

	t_args			args;

	t_timespec		startup;
	t_init_records	init_records;
}					t_sim;

int					init_simulation(t_sim *sim, t_monitor *monitor,
						char **argv);
short				sim_action(short choice, t_timespec *abstime);
void				preseed_dongles_heap(t_sim *sim);
void				preseed_coders_firstcompile(t_sim *sim);

void				_init_sim_ta(t_sim *sim);
int					_create_coder(t_coder *coder, int order, t_sim *sim);
int					_init_dongle(int order, t_sim *sim);

#endif
