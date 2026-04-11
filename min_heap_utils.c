/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:08:08 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/10 10:41:06 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	compare_coders(t_coder *a, t_coder *b, t_input *input)
{
	long	now;

	if (!a || !b)
		return (0);
	if (!strcmp("fifo", input->scheduler))
		return (a->request_time < b->request_time);
	else if (!strcmp("edf", input->scheduler))
	{
		now = get_time(0, input);
		return (((a->last_compile + input->time_to_burnout)
				- now) < ((b->last_compile + input->time_to_burnout) - now));
	}
	return (-1);
}

void	heapify_up(t_heap *heap)
{
	int		i;
	t_coder	*tmp;

	i = heap->heap_size - 1;
	while (i > 0 && compare_coders(heap->coders[i], heap->coders[(i - 1) / 2],
			heap->coders[0]->input))
	{
		tmp = heap->coders[i];
		heap->coders[i] = heap->coders[(i - 1) / 2];
		heap->coders[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
}

static void	initalizer(int idx, int *left_child, int *right_child,
		int *smallest)
{
	*left_child = (idx * 2) + 1;
	*right_child = (idx * 2) + 2;
	*smallest = idx;
}

static void	switch_coders(t_heap *heap, int smallest, int idx)
{
	t_coder	*tmp;

	tmp = heap->coders[smallest];
	heap->coders[smallest] = heap->coders[idx];
	heap->coders[idx] = tmp;
	idx = smallest;
}

void	heapify_down(t_heap *heap, int idx)
{
	int		left_child;
	int		right_child;
	int		smallest;

	while (1)
	{
		initalizer(idx, &left_child, &right_child, &smallest);
		if (left_child < heap->heap_size
			&& compare_coders(heap->coders[left_child], heap->coders[smallest],
				heap->coders[0]->input))
			smallest = left_child;
		if (right_child < heap->heap_size
			&& compare_coders(heap->coders[right_child], heap->coders[smallest],
				heap->coders[0]->input))
			smallest = right_child;
		if (smallest != idx)
		{
			switch_coders(heap, smallest, idx);
		}
		else
			break ;
	}
}
