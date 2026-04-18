/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 16:02:54 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 16:02:57 by otahiri-         ###   ########.fr       */
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
	lock_mutex(coder);
	if (coder->left->cooldown > 0 && coder->right->cooldown > 0)
	{
		if (coder->left->next_available > get_time(0, input)
			|| coder->right->next_available > get_time(0, input))
		{
			unlock_mutex(coder);
			ft_usleep(longest_wait(coder->left, coder->right, input),
					coder);
			return (0);
		}
		coder->left->cooldown = -1;
		printf("%ld %d taken a dongle\n", get_time(input->start, input), coder->id);
		coder->right->cooldown = -1;
		printf("%ld %d taken a dongle\n", get_time(input->start, input), coder->id);
		unlock_mutex(coder);
		return (1);
	}
	else
	{
		unlock_mutex(coder);
		cond_wait(coder);
		return (0);
	}
}

void	aquire_dongles(t_coder *coder, t_input *input)
{
	heap_insert(coder->left->heap, coder, input);
	heap_insert(coder->right->heap, coder, input);
	while (1)
	{
		if (lock_dongles(coder, input))
			break ;
	}
	heap_pop(coder->left->heap, input);
	heap_pop(coder->right->heap, input);
}

void	release_dongle(t_coder *coder, t_input *input)
{
	lock_mutex(coder);
	coder->left->cooldown = 1;
	coder->right->cooldown = 1;
	coder->left->next_available = get_time(0, input) + input->dongle_cooldown;
	coder->right->next_available = get_time(0, input) + input->dongle_cooldown;
	unlock_mutex(coder);
	pthread_cond_broadcast(&coder->left->lock->cond);
	pthread_cond_broadcast(&coder->right->lock->cond);
}
