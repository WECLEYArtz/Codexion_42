/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:05:58 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/18 01:35:15 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../dependencies.h"
# include "../monitor/monitor.h"

// NOTE:	the reason we have sim is usually just to access sim->params.
// 			try to optimise if uneeded later
typedef struct s_coder
{
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
}					t_coder;

void				*coder_routine(void *coder_p);
int					first_compile(t_coder *coder);
void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);

#endif
