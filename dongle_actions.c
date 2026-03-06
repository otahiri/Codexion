/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 12:24:31 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/06 13:03:23 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	aquire_dongles(t_coder *coder)
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
