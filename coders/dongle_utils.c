/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:44:40 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/19 15:00:45 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

long	longest_wait(t_coder *coder, t_input *input)
{
	long	res;
	long	left_next;
	long	right_next;

	pthread_mutex_lock(&coder->left->lock->mutex);
	left_next = coder->left->next_available;
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	right_next = coder->right->next_available;
	pthread_mutex_unlock(&coder->right->lock->mutex);
	if (left_next > right_next)
		res = left_next - get_time(0, input);
	else
		res = right_next - get_time(0, input);
	return (res);
}

void	cond_wait(t_coder *coder)
{
	int	left_cooldown;
	int	right_cooldown;

	pthread_mutex_lock(&coder->left->lock->mutex);
	left_cooldown = coder->left->cooldown;
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	right_cooldown = coder->right->cooldown;
	pthread_mutex_unlock(&coder->right->lock->mutex);
	if (left_cooldown < 0)
		pthread_cond_wait(&coder->left->lock->cond, &coder->left->lock->mutex);
	else if (right_cooldown < 0)
		pthread_cond_wait(&coder->right->lock->cond,
			&coder->right->lock->mutex);
}

void	set_cooldown(t_coder *coder, t_input *input)
{
	printf("%ld %d taken a dongle\n", get_time(input->start, input),
		coder->id);
	printf("%ld %d taken a dongle\n", get_time(input->start, input),
		coder->id);
	reverse_cooldown(coder);
}

void	reverse_cooldown(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->lock->mutex);
	coder->left->cooldown = coder->left->cooldown;
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	coder->right->cooldown = coder->right->cooldown;
	pthread_mutex_unlock(&coder->right->lock->mutex);
}
