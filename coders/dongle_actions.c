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

int	lock_dongles(t_coder *coder)
{
	long		wait;
	t_input		*input;
	t_dongle	*left;
	t_dongle	*right;

	pthread_mutex_lock(&coder->lock->mutex);
	left = coder->left;
	right = coder->right;
	input = coder->input;
	if (left->cooldown > 0 && right->cooldown > 0 && peak(left) == coder->id
		&& peak(right) == coder->id)
	{
		if (left->next_available > get_time(0, input)
			|| right->next_available > get_time(0, input))
		{
			wait = longest_wait(left, right, input);
			pthread_mutex_unlock(&coder->lock->mutex);
			ft_usleep(wait, coder);
			return (0);
		}
		pthread_mutex_unlock(&coder->lock->mutex);
		set_cooldown(coder, input);
		return (1);
	}
	cond_wait(coder);
	pthread_mutex_unlock(&coder->lock->mutex);
	return (0);
}

void	aquire_dongles(t_coder *coder)
{
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
	t_input		*input;
	t_dongle	*left;
	t_dongle	*right;

	pthread_mutex_lock(&coder->lock->mutex);
	left = coder->left;
	right = coder->right;
	input = coder->input;
	revers_cooldown(coder);
	left->next_available = get_time(0, input) + input->dongle_cooldown;
	right->next_available = get_time(0, input) + input->dongle_cooldown;
	pthread_mutex_unlock(&coder->lock->mutex);
	pthread_cond_broadcast(&right->lock->cond);
	pthread_cond_broadcast(&left->lock->cond);
}
