/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 15:34:43 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/30 20:15:07 by wec              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../dependencies.h"

void		announce(t_coder *coder, short action, bool force);
void		cleaner(t_sim *sim);
void		join_coders(t_coder *coder, int count);

t_timespec	get_abstime(t_timespec *last_compile, t_time_add *timeadd);

#endif
