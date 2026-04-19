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
	dongle->lock = create_mutex();
	return (dongle);
}

int	lock_dongles(t_coder *coder, t_input *input)
{
	long			wait;
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	if (coder->left->cooldown > 0 && coder->right->cooldown > 0
		&& peak(coder->left) == coder->id && peak(coder->right) == coder->id)
	{
		if (coder->left->next_available > get_time(0, input)
			|| coder->right->next_available > get_time(0, input))
		{
			wait = longest_wait(coder->left, coder->right, input);
			pthread_mutex_unlock(&lock);
			ft_usleep(wait, coder);
			return (0);
		}
		pthread_mutex_unlock(&lock);
		set_cooldown(coder, input);
		return (1);
	}
	cond_wait(coder);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	return (0);
}

void	aquire_dongles(t_coder *coder)
{
	t_input			*input;
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	input = coder->input;
	heap_insert(coder, input);
	pthread_mutex_unlock(&lock);
	while (1)
	{
		if (lock_dongles(coder, input))
			break ;
	}
	pthread_mutex_lock(&lock);
	heap_pop(coder, input);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
}

void	release_dongle(t_coder *coder)
{
	t_input			*input;
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	input = coder->input;
	revers_cooldown(coder);
	coder->left->next_available = get_time(0, input) + input->dongle_cooldown;
	coder->right->next_available = get_time(0, input) + input->dongle_cooldown;
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	pthread_cond_broadcast(&coder->right->lock->cond);
	pthread_cond_broadcast(&coder->left->lock->cond);
}
