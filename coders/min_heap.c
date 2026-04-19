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

void	heap_pop(t_coder *coder)
{
	t_dongle		*left;
	t_dongle		*right;
	t_input			*input;
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	left = coder->left;
	right = coder->right;
	input = coder->input;
	pthread_mutex_unlock(&lock);
	pthread_mutex_lock(&left->lock->mutex);
	pthread_mutex_lock(&right->lock->mutex);
	printf("%p is left and %p is right\n", (void *)&left->lock->mutex,
		(void *)&right->lock->mutex);
	left->heap->size--;
	right->heap->size--;
	left->heap->coders[0] = left->heap->coders[left->heap->size];
	right->heap->coders[0] = right->heap->coders[right->heap->size];
	left->heap->coders[left->heap->size] = NULL;
	right->heap->coders[right->heap->size] = NULL;
	heapify_down(left->heap, input);
	heapify_down(right->heap, input);
	pthread_mutex_unlock(&right->lock->mutex);
	pthread_mutex_unlock(&left->lock->mutex);
}

void	heap_insert(t_coder *coder)
{
	t_dongle		*left;
	t_dongle		*right;
	t_input			*input;
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	left = coder->left;
	right = coder->right;
	input = coder->input;
	pthread_mutex_unlock(&lock);
	pthread_mutex_lock(&right->lock->mutex);
	pthread_mutex_lock(&left->lock->mutex);
	left->heap->coders[left->heap->size] = coder;
	left->heap->size++;
	heapify_up(left->heap, input);
	right->heap->coders[right->heap->size] = coder;
	right->heap->size++;
	heapify_up(right->heap, input);
	pthread_mutex_unlock(&left->lock->mutex);
	pthread_mutex_unlock(&right->lock->mutex);
}

int	peak(t_dongle *dongle)
{
	return (dongle->heap->coders[0]->id);
}
