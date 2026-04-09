/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:47:06 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/09 10:30:29 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap	*create_heap(t_input *input)
{
	t_heap	*heap;
	int		i;

	i = 0;
	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->heap_cap = input->coders_count;
	heap->heap_size = 0;
	heap->coders = malloc(sizeof(t_coder *) * input->coders_count);
	if (!heap->coders)
	{
		free(heap);
		return (NULL);
	}
	while (i < heap->heap_cap)
		heap->coders[i++] = NULL;
	return (heap);
}

t_coder	*pop_smallest(t_dongle *dongle)
{
	t_coder	*smallest;
	t_heap	*heap;

	heap = dongle->heap;
	smallest = heap->coders[0];
	if (!smallest)
		return (NULL);
	heap->coders[0] = heap->coders[heap->heap_size - 1];
	heap->coders[heap->heap_size - 1] = NULL;
	heap->heap_size--;
	heapify_down(heap, 0);
	return (smallest);
}

void	insert_heap(t_coder *coder, t_dongle *dongle)
{
	t_heap			*heap;

	pthread_mutex_lock(&coder->lock);
	heap = dongle->heap;
	heap->coders[heap->heap_size] = coder;
	heap->heap_size++;
	heapify_up(heap);
	pthread_mutex_unlock(&coder->lock);
}

t_coder	*peak_top(t_dongle *dongle)
{
	return (dongle->heap->coders[0]);
}
