/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:47:06 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/07 09:11:05 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap	*create_heap(t_input *input)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->heap_cap = input->coders_count;
	heap->heap_size = 0;
	heap->coders = malloc(sizeof(t_coder *) * input->coders_count);
	return (heap);
}

void	pop_smallest(t_heap *heap)
{
}

void	insert_heap(t_coder *coder, t_dongle *dongle)
{
	t_heap	*heap;
	int		i;

	i = ((heap->heap_size) / 2) % heap->heap_cap;
	heap = dongle->heap;
	heap->coders[i] = coder;
	heap->heap_size++;
	hepify_up(heap);
}
