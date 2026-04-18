/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:06:47 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 10:12:03 by otahiri-         ###   ########.fr       */
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
	dongle->lock = malloc(sizeof(t_mutex));
	if (!dongle->lock)
	{
		free(dongle->heap);
		free(dongle);
		return (NULL);
	}
	dongle->next_available = get_time(0, input);
	return (dongle);
}

long	longest

int	lock_dongle(t_coder *coder)
{
	long	wait_left;
	long	wait_right;
	long	longest;

	if (coder->left->cooldown > 0 && coder->right->cooldown > 0)
	{
		wait_left = coder->left->next_available - get_time(0, coder->input);
		wait_right = coder->right->next_available - get_time(0, coder->input);
		if
		coder->left->cooldown = -1

	}
}

void	aquire_dongles(t_coder *coder)
{
	
}
