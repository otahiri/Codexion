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

void	activate_switch(t_coder *coder)
{
	pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
	coder->input->kill_switch->kill_switch = 1;
	pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
}

void	acquire_dongle(t_dongle *dongle, t_coder *coder)
{
	long	time;

	pthread_mutex_lock(&dongle->lock->mutex);
	coder->request_time = get_time(0);
	if (coder->request_time == -1 || insert_heap(coder, dongle) == -1)
		activate_switch(coder);
	if (dongle->cooldown < 0)
		pthread_cond_wait(&dongle->lock->cond, &dongle->lock->mutex);
	while (1)
	{
		if (dongle->cooldown >= 0 && coder->id == peak_top(dongle)->id)
		{
			time = get_time(0);
			if (time == -1)
				activate_switch(coder);
			ft_usleep((dongle->next_availabe - time) * 1000);
			dongle->cooldown = -1;
			if (!pop_smallest(dongle))
				return (activate_switch(coder));
			time = get_time(coder->input->start);
			printf("%ld %d has taken a dongle\n", time, coder->id);
			break ;
		}
	}
	pthread_mutex_unlock(&dongle->lock->mutex);
}

void	release_dongle(t_dongle *dongle, t_input *input)
{
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	dongle->next_availabe = get_time(0) + input->dongle_cooldown;
	dongle->cooldown = 1;
	pthread_cond_broadcast(&dongle->lock->cond);
	pthread_mutex_unlock(&dongle->lock->mutex);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
}
