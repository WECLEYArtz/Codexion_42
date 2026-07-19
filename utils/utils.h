/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 15:34:43 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 15:35:02 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../dependencies.h"

void		announce(t_coder *coder, short action, bool force);
void		cleaner(t_sim *sim);
void		join_coders(pthread_t *coders_threads, int count);

t_timespec	get_abstime(t_timespec *last_compile, t_timeadd *timeadd);

#endif
