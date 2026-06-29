/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 11:00:49 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/06/29 17:17:31 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DONGLE_H
# define DONGLE_H

# include "../dependencies.h"

typedef struct s_dongle
{
	t_coder	*duel_slots[2];
	int		cooldown;
	void	(*request)(int id);
	void	(*letgo)(int id);
}			t_dongle;

#endif
