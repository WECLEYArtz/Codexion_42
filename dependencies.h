/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:16:54 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/04 12:52:37 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEPENDENCIES_H
# define DEPENDENCIES_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_sim		t_sim;
typedef struct s_args		t_args;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_monitor	t_monitor;

typedef struct timeval		t_timeval;

// Util functions
void						announce(t_coder *coder, char *action);
void						cleaner(t_sim *sim, int step);
void						join_coders_threads(t_monitor *monitor);

#endif
