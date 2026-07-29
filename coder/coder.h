/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:05:58 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/29 22:00:44 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../dependencies.h"

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				compiles_count;

	t_dongle		*dongle_r;
	t_dongle		*dongle_l;
	pthread_mutex_t	compiled_mutex;
	pthread_cond_t	*monitor_link;
	t_coder			*previous;
	t_coder			*next;

	t_timespec		last_compile;
	t_timespec		burnout_date;

	t_sim			*sim;
}					t_coder;

void				coder_compiled_status_update(t_coder *coder);
void				*coder_routine(void *coder_p);
void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);

#endif
