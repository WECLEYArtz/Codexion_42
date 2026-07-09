/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnoutpq_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/09 12:25:57 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "./monitor.h"

static void	_addback(t_burnoutpq_node **head_p, t_burnoutpq_node *node)
{
	t_burnoutpq_node	*head;

	head = *head_p;
	if(head == node && !node->next)
		return;
	if (!head)
	{
		*head_p = node;
		return;
	}
	if (node->previous && node->next)
	{
		node->previous->next = node->next;
		node->next->previous = node->previous;
	}
	else if (head == node && node->next)
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

static t_burnoutpq_node	*_burnoutpq_handler(short choice,
		t_burnoutpq_node *node)
{
	static pthread_mutex_t	burnoutpq_mutex = PTHREAD_MUTEX_INITIALIZER;
	static t_burnoutpq_node	*head = NULL;
	t_burnoutpq_node		*tmp;

	pthread_mutex_lock(&burnoutpq_mutex);
	if (choice == MVBACK)
		_addback(&head, node);
	else if (choice == POP)
	{
		tmp = head;
		head = head->next;
		return (pthread_mutex_unlock(&burnoutpq_mutex), tmp);
	}
	pthread_mutex_unlock(&burnoutpq_mutex);
	return (NULL);
}

t_burnoutpq_node	*burnoutpq_pop(void)
{
	return (_burnoutpq_handler(POP, NULL));
}

void	burnoutpq_mvback(t_burnoutpq_node *node)
{
	_burnoutpq_handler(MVBACK, node);
}
