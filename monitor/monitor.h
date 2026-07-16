/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:41:30 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/16 13:43:24 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONITOR_H
# define MONITOR_H

# define MVBACK 0
# define POP 1
# define MWATCH 2
# define GWAKE 4

# include "../dependencies.h"
# include "../parser/parser.h"

typedef struct s_burnoutpq_node
{
	t_coder					*coder;
	struct s_burnoutpq_node	*previous;
	struct s_burnoutpq_node	*next;
}							t_burnoutpq_node;

typedef struct s_monitor
{
	pthread_t				thread;
	pthread_cond_t			general_cond;
	pthread_t				*coders_threads;
	pthread_cond_t			*monitor_router;
}							t_monitor;

t_coder						*burnoutpq_pop(void);
void						burnoutpq_mvback(t_burnoutpq_node *node);
void						burnoutpq_monitor_watch(t_monitor *monitor);
void						burnoutpq_monitor_gwake(pthread_cond_t *gcond);

t_coder						*burnoutpq_action(short choice, void *pointer);

#endif
