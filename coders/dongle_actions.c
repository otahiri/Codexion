/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:02:54 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/19 11:30:20 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>

t_dongle	*create_dongle(t_input *input)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->cooldown = 1;
	dongle->heap = create_heap(input);
	if (!dongle->heap)
	{
		free(dongle);
		return (NULL);
	}
	dongle->lock = create_mutex();
	if (!dongle->lock)
	{
		free(dongle->heap);
		free(dongle);
		return (NULL);
	}
	dongle->next_available = get_time(0, input);
	return (dongle);
}

void	init_vars(long *left_cooldown, long *right_cooldown, long *left_next,
		long *right_next, t_coder *coder)
{
	pthread_mutex_lock(&coder->left->lock->mutex);
	*left_cooldown = coder->left->cooldown;
	*left_next = coder->left->next_available;
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	*right_cooldown = coder->right->cooldown;
	*right_next = coder->right->next_available;
	pthread_mutex_unlock(&coder->right->lock->mutex);
}

int	lock_dongles(t_coder *coder)
{
	long	left_cooldown;
	long	right_cooldown;
	long	left_next;
	long	right_next;

	pthread_mutex_lock(&coder->lock->mutex);
	init_vars(&left_cooldown, &right_cooldown, &left_next, &right_next, coder);
	if (left_cooldown > 0 && right_cooldown > 0
		&& peak(coder->left) == coder->id && peak(coder->right) == coder->id)
	{
		if (left_next > get_time(0, coder->input) || right_next > get_time(0,
				coder->input))
		{
			pthread_mutex_unlock(&coder->lock->mutex);
			ft_usleep(longest_wait(coder, coder->input), coder);
			return (0);
		}
		set_cooldown(coder, coder->input);
		pthread_mutex_unlock(&coder->lock->mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->lock->mutex);
	cond_wait(coder);
	return (0);
}

void	aquire_dongles(t_coder *coder)
{
	coder->request = get_time(coder->input->start, coder->input);
	heap_insert(coder);
	while (1)
	{
		if (lock_dongles(coder))
			break ;
	}
	heap_pop(coder);
}

void	release_dongle(t_coder *coder)
{
	t_input	*input;

	reverse_cooldown(coder);
	pthread_mutex_lock(&coder->lock->mutex);
	input = coder->input;
	pthread_mutex_lock(&coder->left->lock->mutex);
	coder->left->next_available = get_time(0, input) + input->dongle_cooldown;
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	coder->right->next_available = get_time(0, input) + input->dongle_cooldown;
	pthread_mutex_unlock(&coder->right->lock->mutex);
	pthread_cond_signal(&coder->right->lock->cond);
	pthread_cond_signal(&coder->left->lock->cond);
	pthread_mutex_unlock(&coder->lock->mutex);
}
