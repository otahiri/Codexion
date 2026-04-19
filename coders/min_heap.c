/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:33:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/19 15:04:34 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void	lock_mutexes(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
}

void	unlock_mutexes(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_unlock(&coder->right->lock->mutex);
}

void	heap_pop(t_coder *coder)
{
	t_input	*input;

	input = coder->input;
	pthread_mutex_lock(&coder->left->lock->mutex);
	coder->left->heap->size--;
	coder->left->heap->coders[0] = coder->left->heap->coders[coder->left->heap->size];
	coder->left->heap->coders[coder->left->heap->size] = NULL;
	heapify_down(coder->left->heap, input);
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	coder->right->heap->size--;
	coder->right->heap->coders[0] = coder->right->heap->coders[coder->right->heap->size];
	coder->right->heap->coders[coder->right->heap->size] = NULL;
	heapify_down(coder->right->heap, input);
	pthread_mutex_unlock(&coder->right->lock->mutex);
}

void	heap_insert(t_coder *coder)
{
	t_input	*input;

	input = coder->input;
	pthread_mutex_lock(&coder->left->lock->mutex);
	coder->left->heap->coders[coder->left->heap->size] = coder;
	coder->left->heap->size++;
	heapify_up(coder->left->heap, input);
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	coder->right->heap->coders[coder->right->heap->size] = coder;
	coder->right->heap->size++;
	heapify_up(coder->right->heap, input);
	pthread_mutex_unlock(&coder->right->lock->mutex);
}

int	peak(t_dongle *dongle)
{
	int	id;

	pthread_mutex_lock(&dongle->lock->mutex);
	id = dongle->heap->coders[0]->id;
	pthread_mutex_unlock(&dongle->lock->mutex);
	return (id);
}
