/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 14:31:50 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMULATION_H
# define SIMULATION_H

# include "../dependencies.h"
# include "../parser/parser.h"

typedef struct s_sim
{
	t_dongle		*dongles;
	t_coder			*coders;

	t_params		params;
	t_timeval		startup;

	pthread_mutex_t	print_mutex;
	pthread_mutex_t	running_mutex;
	pthread_mutex_t	birth_mutex;
	bool			running;
	bool			birth_wake;
}					t_sim;

t_sim	init_simulation(t_params params);
void	sim_cleaner(t_sim *sim);
// make function to cleanup the whole simulation,
// a cleaner compenent that knows what to d for every elements.

#endif
