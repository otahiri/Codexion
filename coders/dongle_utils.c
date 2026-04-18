/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:44:40 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 16:03:07 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

long	longest_wait(t_dongle *left, t_dongle *right, t_input *input)
{
	if (left->next_available > right->next_available)
		return (left->next_available - get_time(0, input));
	else
		return (right->next_available - get_time(0, input));
}

void	cond_wait(t_coder *coder)
{
	if (coder->left->cooldown < 0)
		pthread_cond_wait(&coder->left->lock->cond, &coder->left->lock->mutex);
	else if (coder->right->cooldown < 0)
		pthread_cond_wait(&coder->right->lock->cond,
			&coder->right->lock->mutex);
	usleep(10000);
}

void	unlock_mutex(t_coder *coder)
{
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_unlock(&coder->right->lock->mutex);
}

void	lock_mutex(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
}
