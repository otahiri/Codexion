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

void	reverse_cooldown(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->lock->mutex);
	dongle->cooldown = !dongle->cooldown;
	pthread_mutex_unlock(&dongle->lock->mutex);
}

void	set_cooldown(t_coder *coder)
{
	if (check_switch(coder->flag))
		return ;
	print_log(coder, " taken  a dongle", coder->input);
	print_log(coder, " taken  a dongle", coder->input);
	reverse_cooldown(coder->left);
	reverse_cooldown(coder->right);
}

void	cond_wait(t_coder *coder)
{
	pthread_mutex_lock(&coder->left->lock->mutex);
	while (coder->left->cooldown && !check_switch(coder->flag))
		pthread_cond_wait(&coder->left->lock->cond, &coder->left->lock->mutex);
	pthread_mutex_unlock(&coder->left->lock->mutex);
	pthread_mutex_lock(&coder->right->lock->mutex);
	while (coder->right->cooldown && !check_switch(coder->flag))
		pthread_cond_wait(&coder->right->lock->cond,
			&coder->right->lock->mutex);
	pthread_mutex_unlock(&coder->right->lock->mutex);
}
