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
#include <pthread.h>

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
}

void	set_cooldown(t_coder *coder, t_input *input)
{
	pthread_mutex_lock(&coder->lock->mutex);
	printf("%ld %d taken a dongle\n", get_time(input->start, input),
		coder->id);
	printf("%ld %d taken a dongle\n", get_time(input->start, input),
		coder->id);
	revers_cooldown(coder);
	pthread_mutex_unlock(&coder->lock->mutex);
}

void	revers_cooldown(t_coder *coder)
{
	coder->right->cooldown = coder->right->cooldown;
	coder->left->cooldown = coder->left->cooldown;
}
