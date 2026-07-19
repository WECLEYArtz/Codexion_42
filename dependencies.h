/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 17:16:54 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 16:45:48 by ahmounsi         ###   ########.fr       */
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

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define RESET "\x1b[0m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"

# define ANNOUCE_COMPILE 255
# define ANNOUCE_DEBUG 0
# define ANNOUCE_REFACTOR 12
# define ANNOUCE_BURNOUT 27

typedef struct s_sim		t_sim;
typedef struct s_args		t_args;
typedef struct s_coder		t_coder;
typedef struct s_dongle		t_dongle;
typedef struct s_monitor	t_monitor;

typedef struct timeval		t_timeval;
typedef struct timespec		t_timespec;
typedef struct s_time_add	t_time_add;

#endif
