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

void	acquire_dongle(t_dongle *dongle)
{
	pthread_mutex_t	lock;

	pthread_mutex_lock(&lock);
	if (dongle->cooldown < 0)
		pthread_cond_wait(&dongle->lock->cond, NULL);
	else if (dongle->cooldown > 0)
		usleep(dongle->next_availabe - get_time(0));
	else
	{
		pthread_mutex_lock(&dongle->lock->mutex);
		dongle->cooldown = -1;
	}
	pthread_mutex_unlock(&lock);
}

void	release_dongle(t_dongle *dongle, t_input *input)
{
	pthread_mutex_t	lock;

	pthread_mutex_lock(&lock);
	dongle->next_availabe = get_time(0) + input->dongle_cooldown;
	dongle->cooldown = 1;
	pthread_mutex_unlock(&dongle->lock->mutex);
	pthread_mutex_unlock(&lock);
}

void	min_heap_pop(t_dongle *dongle, int coder_id)
{
	int	i;

	i = 0;
	while (i)

}
