/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:57:47 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/03 14:24:41 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

long long	get_time(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_usec / 1000) + (tv.tv_sec * 1000)) - start);
}

void	*burn_out(void *arg)
{
	t_coder	**coders;
	int		i;
	int		limit;

	coders = arg;
	limit = coders[0]->values->number_of_coders;
	while (1)
	{
		i = 0;
		while (i < limit)
		{
			pthread_mutex_lock(&coders[i]->burnout);
			if (get_time(0)
				- coders[i]->last_compile > coders[i]->values->time_to_burnout)
			{
				pthread_mutex_unlock(&coders[i]->burnout);
				printf("coder is dead\n");
				return (NULL);
			}
			pthread_mutex_unlock(&coders[i]->burnout);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
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
}
