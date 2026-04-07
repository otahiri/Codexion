/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 09:08:08 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/07 09:11:00 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	compare_coders(t_coder *a, t_coder *b)
{
	t_input	*input;
	long	now;

	input = a->input;
	if (!strcmp("fifo", input->scheduler))
		return (a->request_time < b->request_time);
	else if (!strcmp("edf", input->scheduler))
	{
		now = get_time(0);
		return (((a->last_compile + input->time_to_burnout)
				- now) < ((b->last_compile + input->time_to_burnout) - now));
	}
	return (-1);
}

void	hepify_up(t_heap *heap)
{
	int		i;
	t_coder	*tmp;

	i = heap->heap_size - 1;
	while (i > 0 && compare_coders(heap->coders[i], heap->coders[(i - 1) / 2]))
	{
		tmp = heap->coders[i];
		heap->coders[i] = heap->coders[(i - 1) / 2];
		heap->coders[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
}

void	hepify_down(t_heap *heap, int idx)
{
	int		left_child;
	int		right_child;
	int		smallest;
	t_coder	*tmp;

	while (1)
	{
		left_child = (idx * 2) + 1;
		right_child = (idx * 2) + 2;
		smallest = idx;
		if (left_child < heap->heap_size
			&& compare_coders(heap->coders[left_child], heap->coders[smallest]))
			smallest = left_child;
		if (right_child < heap->heap_size
			&& compare_coders(heap->coders[right_child],
				heap->coders[smallest]))
			smallest = right_child;
		if (smallest != idx)
		{
			tmp = heap->coders[smallest];
			heap->coders[smallest] = heap->coders[idx];
			heap->coders[idx] = tmp;
		}
	}
}
