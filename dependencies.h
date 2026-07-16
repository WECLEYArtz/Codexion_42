/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:16:54 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/16 00:20:32 by ahmounsi         ###   ########.fr       */
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
# include <time.h>
# include <unistd.h>

# define DEBUG 0
# define DEBUGBPQ 0
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define RESET "\x1b[0m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"

typedef struct s_sim		t_sim;
typedef struct s_args		t_args;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_monitor	t_monitor;

typedef struct timeval		t_timeval;
typedef struct timespec		t_timespec;
typedef struct s_timeadd
{
	long					sec;
	long					nsec;
}							t_timeadd;

// Util functions
void						announce(t_coder *coder, char *action, int force);
void						cleaner(t_sim *sim);
void						join_coders(pthread_t *coders_threads, int count);
t_timespec					get_abstime(t_timespec *last_compile,
								t_timeadd *timeadd);

#endif
