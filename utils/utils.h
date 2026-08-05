/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/19 15:34:43 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/05 17:24:30 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../dependencies.h"

# define ANNOUCE_COMPILE 255
# define ANNOUCE_DEBUG 0
# define ANNOUCE_REFACTOR 1
# define ANNOUCE_BURNOUT 2
# define ANNOUCE_SINGLE 3

void		announce(t_coder *coder, short action);
void		join_coders(t_coder *coder, int count);
int			cleaner(t_sim *sim);

t_timespec	get_abstime(t_timespec *last_compile, t_time_add *timeadd);

#endif
