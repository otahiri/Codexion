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

static int	compare_coders(t_coder *a, t_coder *b, t_input *input)
{
	long	now;

	if (!strcmp("fifo", input->scheduler))
		return (a->request_time < b->request_time);
	else if (!strcmp("edf", input->scheduler))
	{
		now = get_time(0);
		if (now == -1)
			return (-1);
		return (((a->last_compile + input->time_to_burnout)
				- now) < ((b->last_compile + input->time_to_burnout) - now));
	}
	return (-1);
}

int	heapify_up(t_heap *heap)
{
	int		i;
	int		comparison;
	t_coder	*tmp;

	i = heap->heap_size - 1;
	comparison = compare_coders(heap->coders[i], heap->coders[(i - 1) / 2],
			heap->coders[0]->input);
	while (i > 0 && comparison)
	{
		if (comparison == -1)
			return (-1);
		tmp = heap->coders[i];
		heap->coders[i] = heap->coders[(i - 1) / 2];
		heap->coders[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
		comparison = compare_coders(heap->coders[i], heap->coders[(i - 1) / 2],
				heap->coders[0]->input);
	}
	return (0);
}

static void	initalizer(int idx, long **value, t_heap *heap)
{
	*value[0] = (idx * 2) + 2;
	*value[1] = (idx * 2) + 1;
	*value[3] = idx;
	*value[2] = compare_coders(heap->coders[*value[1]],
			heap->coders[*value[3]], heap->coders[0]->input);
}

int	heapify_down(t_heap *heap, int idx)
{
	long	*value;
	t_coder	*tmp;

	value = malloc(sizeof(int) * 4);
	while (1)
	{
		initalizer(idx, &value, heap);
		if (value[2] == -1)
			return (-1);
		if (value[1] < heap->heap_size && value[2])
			value[3] = value[1];
		if (value[0] < heap->heap_size && value[2])
			value[3] = value[0];
		if (value[3] != idx)
		{
			tmp = heap->coders[value[3]];
			heap->coders[value[3]] = heap->coders[idx];
			heap->coders[idx] = tmp;
			idx = value[3];
		}
		else
			break ;
	}
	free(value);
	return (0);
}
