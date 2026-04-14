/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:12:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/10 10:40:53 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	lock_dongle(t_coder *coder, t_dongle *dongle)
{
	long	time;

	if (check_switch(coder->input))
		return (1);
	if (dongle->cooldown >= 0 && coder->id == peak_top(dongle)->id)
	{
		time = get_time(0, coder->input);
		if (time == -1)
			activate_switch(coder->input);
		ft_usleep((dongle->next_availabe - time), coder);
		dongle->cooldown = -1;
		if (!pop_smallest(dongle))
			return (activate_switch(coder->input));
		time = get_time(coder->input->start, coder->input);
		if (time == -1)
			activate_switch(coder->input);
		printf("%ld %d has taken a dongle\n", time, coder->id);
		return (1);
	}
	return (0);
}

void	acquire_dongle(t_dongle *dongle, t_coder *coder)
{
	pthread_mutex_lock(&dongle->lock->mutex);
	coder->request_time = get_time(0, coder->input);
	if (coder->request_time == -1 || insert_heap(coder, dongle) == -1)
		activate_switch(coder->input);
	if (dongle->cooldown < 0)
		pthread_cond_wait(&dongle->lock->cond, &dongle->lock->mutex);
	while (!lock_dongle(coder, dongle))
	{
		continue ;
	}
	pthread_mutex_unlock(&dongle->lock->mutex);
}

void	release_dongle(t_dongle *dongle, t_input *input)
{
	pthread_mutex_t	lock;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	dongle->next_availabe = get_time(0, input) + input->dongle_cooldown;
	dongle->cooldown = 1;
	pthread_cond_signal(&dongle->lock->cond);
	pthread_mutex_unlock(&dongle->lock->mutex);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
}
