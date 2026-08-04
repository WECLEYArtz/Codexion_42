/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:05:58 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../dependencies.h"

typedef struct s_coder
{
	int				id;
	pthread_t		thread;
	long			compiles_required;

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
void				*single_coder_routine(void *coder_p);
short				compile(t_coder *coder);
short				debug(t_coder *coder);
short				refactor(t_coder *coder);

#endif
