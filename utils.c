/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:57:47 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/06 12:13:37 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"
#include <stdio.h>

long long	get_time(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_usec / 1000) + (tv.tv_sec * 1000)) - start);
}

void	*ret(t_coder *coder)
{
	pthread_mutex_unlock(&coder->burnout);
	printf("%lld %d burned out\n", get_time(coder->start), coder->id);
	return (NULL);
}

void	*burn_out(void *arg)
{
	t_coder		**coders;
	int			i;
	int			limit;
	long long	time;

	coders = arg;
	limit = coders[0]->values->number_of_coders;
	while (1)
	{
		i = 0;
		while (i < limit)
		{
			pthread_mutex_lock(&coders[i]->burnout);
			time = get_time(coders[i]->last_compile);
			if (time > coders[i]->values->time_to_burnout)
				return (ret(coders[i]));
			pthread_mutex_unlock(&coders[i]->burnout);
			i++;
		}
	}
	return (NULL);
}
