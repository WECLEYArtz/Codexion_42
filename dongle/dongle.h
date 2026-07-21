/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/21 16:01:31 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# define DONGLE_CAPACITY 3
# include "../coder/coder.h"

typedef struct s_dongle
{
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	t_coder			*slots[DONGLE_CAPACITY];
	int				cooldown;
	void			(*request)(t_coder *coder);
	void			(*unequip)(t_coder *coder);
}					t_dongle;

void				request(t_dongle *dongle, t_coder *coder);
void				_unequip_fifo_(t_dongle *dongle, t_coder *coder);
void				_unequip_edf_(t_dongle *dongle, t_coder *coder);

#endif
