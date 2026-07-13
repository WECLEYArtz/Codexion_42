/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/13 22:08:09 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../monitor/monitor.h"
# include "../parser/parser.h"

# define STOP 0
# define HOLD 1
# define TOGGLE 2
# define STAT 3

bool				sim_running_status(void);
void				sim_stop(void);
void				sim_launch_hold(void);
void				sim_lauch_toggle(void);

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
	t_timeval		startup;
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
