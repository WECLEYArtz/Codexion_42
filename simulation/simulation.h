/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 14:15:09 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../monitor/monitor.h"
# include "../parser/parser.h"

# define STAT 0
# define WAITRUN 1
# define WAITSTP 2
# define TOGGLE 3

void				sim_toggle(void);
void				sim_wait_run(void);
bool				sim_get_status(void);
void				sim_routine_wait(t_timespec abstime);

typedef struct s_init_records
{
	int				c_thread_init_ok;
	int				c_mutex_init_ok;
	int				m_cond_init_ok;
	int				m_gcond_init_ok;
}					t_init_records;

typedef struct s_sim
{
	t_monitor		monitor;
	t_dongle		*dongles;
	t_coder			*coders;

	t_args			args;

	t_timeadd		ta_burnout;
	t_timeadd		ta_compile;
	t_timeadd		ta_debug;
	t_timeadd		ta_refactor;

	t_timespec		startup;
	t_init_records	init_records;
}					t_sim;

int					init_simulation(t_sim *sim, char **argv);
void				preseed_dongles_heap(t_sim *sim);
void				*monitor(void *t_sim_p);

void				_init_ta(t_timeadd *time, int ms);
int					_fill_coder_vals(t_coder *coder, int order, t_sim *sim);

// ========================
// DEBUGING == DELETE LATER
void				debug_visualise(t_sim *sim);
// DEBUGING == DELETE LATER
// ========================

#endif
