/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:05:58 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/04 12:51:50 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODER_H
# define CODER_H

# include "../dependencies.h"

typedef struct s_coder
{
	int				id;
	int				compiled;

	t_dongle		*dongle_l;
	t_dongle		*dongle_r;
	t_timeval		last_compile;
	pthread_cond_t	*monitor_link;

	t_sim			*sim;
}					t_coder;

void				*coder_routine(void *coder_p);

void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);

#endif
