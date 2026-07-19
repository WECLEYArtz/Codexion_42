/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:41:30 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 17:24:12 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# define MV_BACK 0
# define POP 1
# define M_WATCH 2
# define M_WAKE 4

# include "../dependencies.h"

typedef struct s_monitor
{
	pthread_t				thread;
	pthread_t				*coders_threads;
	pthread_cond_t			*monitor_router;
}							t_monitor;

void						*monitor_routine(void *t_sim_p);
t_coder						*burnout_list_action(short choice, void *pointer);

#endif
