/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnoutpq_control.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/14 02:17:24 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dependencies.h"
#include "./monitor.h"
#include "../coder/coder.h"
#include <fcntl.h>

// static void visualise(t_burnoutpq_node *head, int step)
// {
// 	static pthread_mutex_t hh = PTHREAD_MUTEX_INITIALIZER;
//
// 	pthread_mutex_lock(&hh);
// 	printf("%s\n", step?"[ After ]":"===[ Before ]==========================================");
// 	int limit = 3;
// 	while(head && limit--)
// 	{
// 		printf(">>> Node: %d\n", head->coder? head->coder->id : 404);
// 		printf("    Prev: %d - Next: %d\n",
// 				head->previous? head->previous->coder->id : 404,
// 				head->next? head->next->coder->id : 404);
// 		head = head->next;
// 	}
// 	printf("%s\n",step?"=======================================================\n":"");
// 	pthread_mutex_unlock(&hh);
// }

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
	// if (DEBUGBPQ) visualise(head, 0);
	if (choice == MVBACK)
	{
		// if (DEBUGBPQ) printf(BLUE"[BQ]: adding coder %d\n"RESET, ((t_burnoutpq_node *)pointer)->coder->id);
		_addback(&head, (t_burnoutpq_node *)pointer);
	}
	else if (choice == POP)
	{
		// if (DEBUGBPQ) printf(YELLOW"[BQ]: extracting coder %d\n"RESET, head->coder->id);
		tmp = head;
		head = head->next;
		if (head)
			head->previous = NULL;
		tmp->next = NULL;
		tmp->previous = NULL;
		// if (DEBUGBPQ) visualise(head, 1);
		return (pthread_mutex_unlock(&mutex), tmp->coder);
	}
	else if (choice == MWATCH)
		while (!head)
			pthread_cond_wait(&((t_monitor *)pointer)->general_cond, &mutex);
	// if (DEBUGBPQ) visualise(head, 1);
	pthread_mutex_unlock(&mutex);

	return (NULL);
}

t_coder	*burnoutpq_pop(void)
{
	return (_burnoutpq_handler(POP, NULL));
}

void	burnoutpq_mvback(t_burnoutpq_node *node)
{
	// if (DEBUG) announce(node->coder, RED "[debug] Locking mutex BPQ" RESET);
	_burnoutpq_handler(MVBACK, node);
	// if (DEBUG) announce(node->coder, GREEN "[debug] UnLocking mutex BPQ" RESET);
}

void	burnoutpq_monitor_watch(t_monitor *monitor)
{
	_burnoutpq_handler(MWATCH, monitor);
};
