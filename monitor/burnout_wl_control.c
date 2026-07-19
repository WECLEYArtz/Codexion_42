/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burnout_wl_control.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmounsi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/07 17:31:10 by ahmounsi          #+#    #+#             */
/*   Updated: 2026/07/19 15:31:42 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../coder/coder.h"
#include "./monitor.h"

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

t_coder	*burnout_wl_action(short choice, void *pointer)
{
	static pthread_mutex_t	mutex = PTHREAD_MUTEX_INITIALIZER;
	static pthread_cond_t	fc_cond = PTHREAD_COND_INITIALIZER;
	static t_coder			*head = NULL;
	t_coder					*tmp;

	pthread_mutex_lock(&mutex);
	if (choice == MVBACK)
		_addback(&head, (t_coder *)pointer);
	else if (choice == POP)
	{
		tmp = head;
		head = head->next;
		tmp->next = NULL;
		tmp->previous = NULL;
		if (head)
			head->previous = NULL;
		return (pthread_mutex_unlock(&mutex), tmp);
	}
	else if (choice == MWATCH)
		while (!head)
			pthread_cond_wait(&fc_cond, &mutex);
	else if (choice == MWAKE)
		pthread_cond_signal(&fc_cond);
	pthread_mutex_unlock(&mutex);
	return (NULL);
}
