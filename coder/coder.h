/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:05:58 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 02:35:50 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../dependencies.h"

// NOTE:	the reason we have sim is usually just to access sim->params.
// 			try to optimise if uneeded later
typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				compiled;

	t_dongle		*dongle_r;
	t_dongle		*dongle_l;
	pthread_mutex_t	compiled_mutex;
	pthread_cond_t	*monitor_link;
	t_coder			*previous;
	t_coder			*next;

	t_sim			*sim;
	t_timespec		last_compile;
	t_timespec		burnout_date;
	bool			first_compiler;
}					t_coder;

void				coder_dates_update(t_coder *coder);
void				*coder_routine(void *coder_p);
void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);

#endif
