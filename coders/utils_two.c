/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:58:05 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 15:11:20 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_mutex	*create_mutex(void)
{
	t_mutex	*mutex;

	mutex = malloc(sizeof(t_mutex));
	if (!mutex)
		return (NULL);
	if (pthread_mutex_init(&mutex->mutex, NULL))
	{
		free(mutex);
		return (NULL);
	}
	if (pthread_cond_init(&mutex->cond, NULL))
	{
		free(mutex);
		pthread_mutex_destroy(&mutex->mutex);
		return (NULL);
	}
	return (mutex);
}

void	free_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(&mutex->mutex);
	pthread_cond_destroy(&mutex->cond);
	free(mutex);
}

void	free_dongle(t_dongle *dongle)
{
	free_heap(dongle->heap);
	free_mutex(dongle->lock);
	dongle->lock = NULL;
	free(dongle);
}

void	free_heap(t_heap *heap)
{
	free(heap->coders);
	free_mutex(heap->sleep);
	free(heap);
}

void	print_log(t_coder *coder, char *event, t_input *input)
{
	pthread_mutex_lock(&input->write_lock->mutex);
	printf("%ld %d %s\n", get_time(coder->input->start, coder->input),
		coder->id, event);
	pthread_mutex_unlock(&input->write_lock->mutex);
}
