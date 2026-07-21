/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 10:38:05 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/21 16:35:13 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "../dongle/dongle.h"

void	request(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->mutex);
	while (dongle->slots[0] != coder)
		pthread_cond_wait(&dongle->cond, NULL);
	pthread_mutex_unlock(&dongle->mutex);
}

void	_unequip_fifo_(t_dongle *dongle, t_coder *coder)
{
	t_coder	*tmp;

	pthread_mutex_lock(&dongle->mutex);
	tmp = dongle->slots[0];
	dongle->slots[0] = dongle->slots[1];
	dongle->slots[1] = tmp;
	pthread_mutex_unlock(&dongle->mutex);
}

void	_unequip_edf_(t_dongle *dongle, t_coder *coder)
{
	t_coder	*tmp;

	pthread_mutex_lock(&dongle->mutex);
	tmp = dongle->slots[0];
	// to be worked on
	pthread_mutex_unlock(&dongle->mutex);
}

void	__bubble_down()
{

	__bubble_down9();
}
