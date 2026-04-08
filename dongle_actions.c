/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:12:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/06 12:05:16 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	ft_usleep(long timer)
{
	if (timer > 0)
		return (usleep(timer));
	return (0);
}

void	acquire_dongle(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	coder->request_time = get_time(0);
	insert_heap(coder, dongle);
	while (coder->id != peak_top(dongle)->id)
		ft_usleep(10);
	while (dongle->cooldown < 0)
		ft_usleep(1);
	if (dongle->cooldown >= 0 && coder->id == peak_top(dongle)->id)
	{
		ft_usleep((dongle->next_availabe - get_time(0)) * 1000);
		pthread_mutex_lock(&dongle->lock->mutex);
		dongle->cooldown = -1;
		pop_smallest(dongle);
	}
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
}

void	release_dongle(t_dongle *dongle, t_input *input)
{
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	dongle->next_availabe = get_time(0) + input->dongle_cooldown;
	dongle->cooldown = 1;
	pthread_mutex_unlock(&dongle->lock->mutex);
	pthread_cond_signal(&dongle->lock->cond);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
}
