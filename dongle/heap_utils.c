/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wec <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 18:29:44 by wec               #+#    #+#             */
/*   Updated: 2026/08/04 05:58:18 by ahmounsi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../dongle/dongle.h"

static bool	is_sader(t_coder *coder1, t_coder *coder2)
{
	long	result;

	if (!coder1 || !coder2)
		return (0);
	result = coder1->burnout_date.tv_sec - coder2->burnout_date.tv_sec;
	if (result)
		return (result < 0);
	result = coder1->burnout_date.tv_nsec - coder2->burnout_date.tv_nsec;
	if (result)
		return (result < 0);
	return (coder1 - coder2 < 0);
}

static void	dhq_bubble_down(t_coder **heap, int i)
{
	short	sadest_coder;
	short	left;
	short	right;
	t_coder	*tmp;

	sadest_coder = i;
	left = 2 * i + 1;
	right = 2 * i + 2;
	if (left <= HEAP_SIZE - 1 && is_sader(heap[left], heap[i]))
		sadest_coder = left;
	if (right <= HEAP_SIZE - 1 && is_sader(heap[right], heap[left]))
		sadest_coder = right;
	if (heap[sadest_coder] != heap[i])
	{
		tmp = heap[sadest_coder];
		heap[sadest_coder] = heap[i];
		heap[i] = tmp;
		dhq_bubble_down(heap, sadest_coder);
	}
}

static void	dhq_bubble_up(t_coder **heap, int i)
{
	int		parent;
	t_coder	*tmp;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (is_sader(heap[i], heap[parent]))
		{
			tmp = heap[parent];
			heap[parent] = heap[i];
			heap[i] = tmp;
		}
		else
			return ;
		i = parent;
	}
}

void	dhq_insert(t_dongle *dongle, t_coder *coder)
{
	if (dongle->heap_elements < HEAP_SIZE && dongle->heap[0] != coder)
	{
		dongle->heap[dongle->heap_elements] = coder;
		if (dongle->scheduler == EDF)
			dhq_bubble_up(dongle->heap, dongle->heap_elements);
		dongle->heap_elements++;
	}
}

void	dhq_pop(t_dongle *dongle, t_coder *coder)
{
	int		last_index;
	t_coder	**heap;

	heap = dongle->heap;
	if (heap[0] == coder)
	{
		last_index = dongle->heap_elements - 1;
		heap[0] = heap[last_index];
		heap[last_index] = NULL;
		if (dongle->scheduler == EDF)
			dhq_bubble_down(heap, last_index);
		dongle->heap_elements--;
	}
}
