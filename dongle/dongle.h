/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 17:08:48 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# define HEAP_DEBUG 0

# define HEAP_SIZE 2
# define EDF 0
# define FIFO 1
# include "../coder/coder.h"

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_coder			*heap[HEAP_SIZE];
	int				heap_occupied;

	int				cooldown;
	short			scheduler;

	bool			taken;
	t_timespec		available_date;
	t_sim			*sim;
}					t_dongle;

int					try_take_dongles(t_dongle *dr, t_dongle *dl, t_coder *cdr);
void				untake_dongle(t_dongle *dongle, t_coder *coder);

void				dhq_insert(t_dongle *dongle, t_coder *coder);
void				dhq_pop(t_dongle *dongle, t_coder *coder);

#endif
