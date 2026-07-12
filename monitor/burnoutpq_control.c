/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnoutpq_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/12 00:24:37 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "./monitor.h"
#include "../coder/coder.h"

// static void visualise(t_burnoutpq_node *head, int step)
// {
// 	static pthread_mutex_t hh = PTHREAD_MUTEX_INITIALIZER;
//
// 	pthread_mutex_lock(&hh);
// 	printf(">>> | %s |\n", step?"After":"Before");
// 	int limit = 3;
// 	while(head && limit--)
// 	{
// 		printf(">>> Node: %d\n", head->coder? head->coder->id : 404);
// 		printf("    Prev: %d - Next: %d\n",
// 				head->previous? head->previous->coder->id : 404,
// 				head->next? head->next->coder->id : 404);
// 		head = head->next;
// 	}
// 	pthread_mutex_unlock(&hh);
//
// }

static void	_addback(t_burnoutpq_node **head_p, t_burnoutpq_node *node)
{
	t_burnoutpq_node	*head;

	head = *head_p;
	if (head == node && !node->next)
		return ;
	if (!head)
	{
		*head_p = node;
		return ;
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

static t_coder	*_burnoutpq_handler(short choice, void *pointer)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static t_burnoutpq_node	*head = NULL;
	t_burnoutpq_node		*tmp;


	pthread_mutex_lock(&mutex);
	// visualise(head, 0);
	if (choice == MVBACK)
	{
		// printf("[BQ]: adding coder %p\n", ((t_burnoutpq_node *)pointer)->coder);
		_addback(&head, (t_burnoutpq_node *)pointer);
	}
	else if (choice == POP)
	{
		// printf("[BQ]: extracting coder %p", head->coder);
		tmp = head;
		head = head->next;
		tmp->next = NULL;
		tmp->previous = NULL;
		return (pthread_mutex_unlock(&mutex), tmp->coder);
	}
	else if (choice == MWATCH)
		while (!head)
		{
			// puts("[MONITOR] No head!!");
			pthread_cond_wait(&((t_monitor *)pointer)->general_cond, &mutex);
		}
	// visualise(head, 1);
	pthread_mutex_unlock(&mutex);

	return (NULL);
}

t_coder	*burnoutpq_pop(void)
{
	return (_burnoutpq_handler(POP, NULL));
}

void	burnoutpq_mvback(t_burnoutpq_node *node)
{
	// announce(node->coder ,"Locking mutex BPQ	 [debug]");
	_burnoutpq_handler(MVBACK, node);
	// announce(node->coder ,"UnLocking mutex BPQ	 [debug]");
}

void	burnoutpq_monitor_watch(t_monitor *monitor)
{
	_burnoutpq_handler(MWATCH, monitor);
};
