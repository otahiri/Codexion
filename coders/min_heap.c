/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:33:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/19 11:15:32 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

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

void	heap_pop(t_coder *coder, t_input *input)
{
	t_heap	*left;
	t_heap	*right;

	left = coder->left->heap;
	right = coder->right->heap;
	left->size--;
	right->size--;
	left->coders[0] = left->coders[left->size];
	right->coders[0] = right->coders[right->size];
	left->coders[left->size] = NULL;
	right->coders[right->size] = NULL;
	heapify_down(left, input);
	heapify_down(right, input);
}

void	heap_insert(t_coder *coder, t_input *input)
{
	t_heap	*left;
	t_heap	*right;

	left = coder->left->heap;
	right = coder->right->heap;
	left->coders[left->size] = coder;
	left->size++;
	heapify_up(left, input);
	right->coders[right->size] = coder;
	right->size++;
	heapify_up(right, input);
}

int	peak(t_dongle *dongle)
{
	return (dongle->heap->coders[0]->id);
}
