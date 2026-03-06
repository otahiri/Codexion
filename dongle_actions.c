/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:24:31 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/06 13:01:55 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	aquire_dongles(t_coder *coder)
{
	t_coder	*coder_a;
	t_coder	*coder_b;

	coder_a = peak_top(coder->left);
	coder_b = peak_top(coder->right);
	push_coder(coder->left, coder);
	push_coder(coder->right, coder);
	if (!coder_a || !coder_b)
		return ;
	if (coder->id == coder_a->id && coder->id == coder_b->id)
		lock_dongles(coder);
	else
	{
		pthread_cond_wait(&coder->left->cond_var, &coder->left->dongle);
		pthread_cond_wait(&coder->right->cond_var, &coder->right->dongle);
	}
}

void	lock_dongles(t_coder *coder)
{
	if (coder->id % 2)
	{
		pthread_mutex_lock(&coder->right->dongle);
		printf("%lld %d has taken a dongle\n", get_time(coder->start),
			coder->id);
		pthread_mutex_lock(&coder->left->dongle);
		printf("%lld %d has taken a dongle\n", get_time(coder->start),
			coder->id);
	}
	else
	{
		pthread_mutex_lock(&coder->left->dongle);
		printf("%lld %d has taken a dongle\n", get_time(coder->start),
			coder->id);
		pthread_mutex_lock(&coder->right->dongle);
		printf("%lld %d has taken a dongle\n", get_time(coder->start),
			coder->id);
	}
	pop_coder(coder->left);
	pop_coder(coder->right);
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->right->dongle);
	pthread_mutex_unlock(&coder->left->dongle);
	pthread_cond_broadcast(&coder->left->cond_var);
	pthread_cond_broadcast(&coder->right->cond_var);
}
