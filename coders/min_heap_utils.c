/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 09:13:31 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 09:21:43 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	switch_coders(int a, int b, t_heap *heap)
{
	t_coder	*tmp;

	tmp = heap->coders[a];
	heap->coders[a] = heap->coders[b];
	heap->coders[b] = tmp;
}

int	compare_coder(t_coder *parent, t_coder *child, t_input *input)
{
	if (!strcmp("edf", input->scheduler))
		return (child->last_compile < parent->last_compile);
	else if (!strcmp("fifo", input->scheduler))
	{
		return (child->request < parent->request);
	}
	else
		return (0);
}

void	init_value(t_heap *heap, t_input *input)
{
	int	i;

	i = 0;
	heap->size = 0;
	while (i <= input->number_of_coders)
		heap->coders[i++] = NULL;
}

void	heapify_down(t_heap *heap, t_input *input)
{
	int	smallest;
	int	left;
	int	right;
	int	idx;

	idx = 0;
	while (1)
	{
		smallest = idx;
		left = (smallest * 2) + 1;
		right = (smallest * 2) + 2;
		if (left < heap->size && compare_coder(heap->coders[smallest],
				heap->coders[left], input))
			smallest = left;
		if (right < heap->size && compare_coder(heap->coders[smallest],
				heap->coders[right], input))
			smallest = right;
		if (smallest != idx)
			idx = smallest;
		else
			break ;
	}
}

void	heapify_up(t_heap *heap, t_input *input)
{
	int	idx;

	idx = heap->size - 1;
	while (idx > 0 && compare_coder(heap->coders[(idx - 1) / 2],
			heap->coders[idx], input))
	{
		switch_coders(idx, (idx - 1) / 2, heap);
		idx = (idx - 1) / 2;
	}
}
