/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/16 13:42:25 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../monitor/monitor.h"
# include "../parser/parser.h"

# define OFF 0
# define ON 1
# define STAT 2
# define WAITRUN 3
# define WAITSTP 4

bool				sim_action(short choice, t_timespec *abstime);
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

void				init_sim_ta(t_sim *sim);
int					_fill_coder_vals(t_coder *coder, int order, t_sim *sim);

#endif
