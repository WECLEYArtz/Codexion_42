/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 20:31:30 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../parser/parser.h"

typedef void		(*t_routines)(t_coder *);
typedef struct s_sim
{
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
void				simcleaner(t_sim *sim, int step);
// make function to cleanup the whole simulation,
// a cleaner compenent that knows what to d for every elements.

#endif
