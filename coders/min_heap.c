/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:33:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 09:22:53 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_heap	*create_heap(t_input *input)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	if (!heap)
		return (NULL);
	heap->coders = malloc(sizeof(t_coder *) * (input->number_of_coders + 1));
	if (!heap->coders)
	{
		free(heap);
		return (NULL);
	}
	heap->sleep = malloc(sizeof(t_mutex));
	if (!heap->sleep)
	{
		free(heap->coders);
		free(heap);
		return (NULL);
	}
	init_value(heap, input);
	return (heap);
}

void	heap_pop(t_heap *heap, t_input *input)
{
	heap->size--;
	heap->coders[0] = heap->coders[heap->size];
	heap->coders[heap->size] = NULL;
	heapify_down(heap, input);
}

void	heap_insert(t_heap *heap, t_coder *coder, t_input *input)
{
	heap->coders[heap->size] = coder;
	heap->size++;
	heapify_up(heap, input);
}
