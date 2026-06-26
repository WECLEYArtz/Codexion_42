/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:05:58 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/26 13:05:59 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../dependencies.h"

typedef struct s_coder
{
	pthread_t		thread;
	pthread_cond_t	birth_control;
	int				id;

	int				time_to_burnout;
	int				compiled;
	int				last_compile;

	t_dongle		*dongle_l;
	t_dongle		*dongle_r;

	t_sim			*sim;
}					t_coder;

void				*coder_routine(void *coder_p);

void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);

#endif
