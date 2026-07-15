/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnoutpq_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/15 16:48:02 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "./monitor.h"
#include "../coder/coder.h"

static void	_addback(t_burnoutpq_node **head_p, t_burnoutpq_node *node)
{
	t_burnoutpq_node	*head;

	head = *head_p;
	if (!head)
	{
		*head_p = node;
		return ;
	}
	if (head == node && !node->next)
		return ;
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
	if (head == node && node->next)
	{
		*head_p = node->next;
		(*head_p)->previous = NULL;
	}
	while (head->next)
		head = head->next;
	head->next = node;
	node->previous = head;
	node->next = NULL;
}

static t_coder	*_burnoutpq_handler(short choice, void *pointer)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static t_burnoutpq_node	*head = NULL;
	t_burnoutpq_node		*tmp;


	pthread_mutex_lock(&mutex);
	if (choice == MVBACK)
	{
		_addback(&head, (t_burnoutpq_node *)pointer);
	}
	else if (choice == POP)
	{
		tmp = head;
		head = head->next;
		if (head)
			head->previous = NULL;
		tmp->next = NULL;
		tmp->previous = NULL;
		return (pthread_mutex_unlock(&mutex), tmp->coder);
	}
	else if (choice == MWATCH)
		while (!head)
			pthread_cond_wait(&((t_monitor *)pointer)->general_cond, &mutex);
	else if (choice == GWAKE)
		pthread_cond_signal((pthread_cond_t *)pointer);
	pthread_mutex_unlock(&mutex);

	return (NULL);
}

t_coder	*burnoutpq_pop(void)
{
	return (_burnoutpq_handler(POP, NULL));
}

void	burnoutpq_mvback(t_burnoutpq_node *node)
{
	_burnoutpq_handler(MVBACK, node);
}

void	burnoutpq_monitor_watch(t_monitor *monitor)
{
	_burnoutpq_handler(MWATCH, monitor);
}

void	burnoutpq_monitor_gwake(pthread_cond_t *general_cond)
{
	_burnoutpq_handler(GWAKE, general_cond);
}
