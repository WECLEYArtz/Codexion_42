/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout_wl_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/27 16:23:41 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "./monitor.h"
#include <stdbool.h>

static void	_addback(t_coder **head_p, t_coder *node)
{
	t_coder	*head;

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

static t_coder	*_pop(t_coder **head_p, pthread_mutex_t *mutex)
{
	t_coder	*tmp;

	tmp = *head_p;
	*head_p = (*head_p)->next;
	tmp->next = NULL;
	tmp->previous = NULL;
	if (*head_p)
		(*head_p)->previous = NULL;
	pthread_mutex_unlock(mutex);
	return (tmp);
}

t_coder	*burnout_list_action(short choice, void *pointer)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	first_add_condr = PTHREAD_COND_INITIALIZER;
	static t_coder			*head = NULL;
	static bool				monitor_started = false;

	pthread_mutex_lock(&mutex);
	if (choice == MV_BACK)
	{
		_addback(&head, (t_coder *)pointer);
		if(monitor_started == false)
		{
			pthread_cond_signal(&first_add_condr);
			monitor_started = true;
		}
	}
	else if (choice == POP)
		return (_pop(&head, &mutex));
	else if (choice == M_WATCH)
		while (!head)
			pthread_cond_wait(&first_add_condr, &mutex);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}
