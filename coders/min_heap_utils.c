/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 09:13:31 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/30 11:54:37 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	switch_coders(int *a, int *b, t_heap *heap)
{
	t_coder	*tmp;

	*a = *b;
	tmp = heap->coders[*a];
	heap->coders[*a] = heap->coders[*b];
	heap->coders[*b] = tmp;
}

int	compare_coder(t_coder *parent, t_coder *child, t_input *input)
{
	long	child_last_comp;
	long	parent_last_comp;
	long	child_request;
	long	parent_request;

	pthread_mutex_lock(&child->lock->mutex);
	child_last_comp = child->last_compile;
	child_request = child->request;
	pthread_mutex_unlock(&child->lock->mutex);
	pthread_mutex_lock(&parent->lock->mutex);
	parent_last_comp = parent->last_compile;
	parent_request = parent->request;
	pthread_mutex_unlock(&parent->lock->mutex);
	if (!strcmp("edf", input->scheduler))
	{
		if (child->last_compile == parent->last_compile)
			return (child->id < parent->id);
		else
			return (child->last_compile < parent->last_compile);
	}
	else if (!strcmp("fifo", input->scheduler))
		return (child->request < parent->request);
	else
		return (0);
}

void	pointless(int *smallest, int *left, int *right, int idx)
{
	*smallest = idx;
	*left = (*smallest * 2) + 1;
	*right = (*smallest * 2) + 2;
}

void	heapify_down(t_dongle *dongle, t_input *input)
{
	int		s;
	int		l;
	int		r;
	int		i;
	t_heap	*heap;

	i = 0;
	heap = dongle->heap;
	pthread_mutex_lock(&dongle->lock->mutex);
	while (1)
	{
		pointless(&s, &l, &r, i);
		if (l < heap->size && compare_coder(heap->coders[s], heap->coders[l],
				input))
			s = l;
		if (r < heap->size && compare_coder(heap->coders[s], heap->coders[r],
				input))
			s = r;
		if (s != i)
			switch_coders(&i, &s, heap);
		else
			break ;
	}
	pthread_mutex_unlock(&dongle->lock->mutex);
}

void	heapify_up(t_dongle *dongle, t_input *input)
{
	int		idx;
	t_coder	*tmp;

	pthread_mutex_lock(&dongle->lock->mutex);
	idx = dongle->heap->size - 1;
	while (idx > 0 && compare_coder(dongle->heap->coders[(idx - 1) / 2],
			dongle->heap->coders[idx], input))
	{
		tmp = dongle->heap->coders[idx];
		dongle->heap->coders[idx] = dongle->heap->coders[(idx - 1) / 2];
		dongle->heap->coders[(idx - 1) / 2] = tmp;
		idx = (idx - 1) / 2;
	}
	pthread_mutex_unlock(&dongle->lock->mutex);
}
