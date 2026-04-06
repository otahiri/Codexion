/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 10:47:06 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/06 12:05:17 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

t_heap	*create_heap(t_input *input)
{
	t_heap	*heap;

	heap = malloc(sizeof(t_heap));
	heap->heap_cap = input->coders_count;
	heap->heap_size = 0;
	return (heap);
}

int	

int	compare_edf(t_coder *a, t_coder *b)
{
	long	a_burn_out;
	long	b_burn_out;

	a_burn_out = a->last_compile + a->input->time_to_burnout;
	b_burn_out = b->last_compile + b->input->time_to_burnout;
	return (a_burn_out > b_burn_out);
}

void	ft_sort_min_heap(t_heap *heap)
{
	int	i;
	int	j;

	i = 0;
	while (i < heap->heap_size)
	{
		j = 0;
		while (j < heap->heap_size)
		{
			if 
			j++;
		}
		i++;
	}
}
