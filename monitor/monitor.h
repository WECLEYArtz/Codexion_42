/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 21:41:30 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/09 12:25:11 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MONTIR_H
# define MONTIR_H

# define MVBACK 0
# define POP 1

# include "../dependencies.h"
# include "../parser/parser.h"

typedef struct s_burnoutpq_node
{
	int id;
	struct s_burnoutpq_node	*previous;
	t_coder					*coder;
	struct s_burnoutpq_node	*next;
}							t_burnoutpq_node;

typedef struct s_monitor
{
	pthread_t				thread;
	pthread_t				*coders_threads;
	pthread_cond_t			*monitor_router;
}							t_monitor;

t_burnoutpq_node			*burnoutpq_pop(void);
void						burnoutpq_mvback(t_burnoutpq_node *node);

// ========================
// DEBUGING == DELETE LATER
	void	debug_visualise();
// DEBUGING == DELETE LATER
// ========================
#endif
