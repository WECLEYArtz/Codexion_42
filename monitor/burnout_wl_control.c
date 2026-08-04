/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout_wl_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "./monitor.h"

static void	_addback(t_coder **head_root, t_coder *node)
{
	static t_coder	*tail = NULL;
	t_coder			*head;

	head = *head_root;
	if ((head == node && node->next == NULL) || (tail == node))
		return ;
	if (!head)
	{
		*head_root = node;
		tail = node;
		return ;
	}
	if (head == node)
		*head_root = node->next;
	if (node->previous)
		node->previous->next = node->next;
	if (node->next)
		node->next->previous = node->previous;
	tail->next = node;
	node->previous = tail;
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
	static pthread_cond_t	sig_new_add = PTHREAD_COND_INITIALIZER;
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static t_coder			*head = NULL;
	static bool				monitor_started = false;

	pthread_mutex_lock(&mutex);
	if (choice == MV_BACK)
	{
		_addback(&head, (t_coder *)pointer);
		if (monitor_started == false)
		{
			pthread_cond_signal(&sig_new_add);
			monitor_started = true;
		}
	}
	else if (choice == POP)
		return (_pop(&head, &mutex));
	else if (choice == M_WATCH)
		while (!head)
			pthread_cond_wait(&sig_new_add, &mutex);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}
