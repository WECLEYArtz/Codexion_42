/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 15:34:43 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/31 18:35:08 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../dependencies.h"

void		announce(t_coder *coder, short action, bool force);
void		single_announce(t_coder *coder, bool force);
void		join_coders(t_coder *coder, int count);
int			cleaner(t_sim *sim);

t_timespec	get_abstime(t_timespec *last_compile, t_time_add *timeadd);

#endif
