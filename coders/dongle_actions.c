/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:12:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/15 14:47:08 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

int	lock_dongle(t_coder *coder, t_dongle *dongle)
{
	if (dongle->cooldown >= 0 && coder->id == peak_top(dongle)->id)
	{
		ft_usleep((dongle->next_availabe - get_time(0, coder->input)), coder);
		if (check_switch(coder->input))
			return (1);
		dongle->cooldown = -1;
		pop_smallest(dongle);
		if (check_switch(coder->input))
			return (1);
		printf("%ld %d has taken a dongle\n", get_time(coder->input->start,
				coder->input), coder->id);
		pthread_mutex_unlock(&dongle->lock->mutex);
		return (1);
	}
	else
		pthread_cond_wait(&dongle->lock->cond, &dongle->lock->mutex);
	return (0);
}

void	acquire_dongle(t_dongle *dongle, t_coder *coder)
{
	insert_heap(coder, dongle);
	coder->request_time = get_time(0, coder->input);
	if (dongle->cooldown < 0)
		pthread_cond_wait(&dongle->lock->cond, &dongle->lock->mutex);
	while (!lock_dongle(coder, dongle))
	{
		if (check_switch(coder->input))
			return ;
		continue ;
	}
}

void	release_dongle(t_dongle *dongle, t_input *input)
{
	pthread_mutex_lock(&dongle->lock->mutex);
	dongle->next_availabe = get_time(0, input) + input->dongle_cooldown;
	dongle->cooldown = 1;
	pthread_cond_signal(&dongle->lock->cond);
	pthread_mutex_unlock(&dongle->lock->mutex);
}
