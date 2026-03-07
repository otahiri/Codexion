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

long long	get_time(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_usec / 1000) + (tv.tv_sec * 1000)) - start);
}

void	*ret(t_coder *coder)
{
	pthread_mutex_t	stop_sign;

	pthread_mutex_init(&stop_sign, NULL);
	pthread_mutex_lock(&stop_sign);
	pthread_mutex_unlock(&coder->values->burnout);
	coder->values->stop = 1;
	printf("%lld %d burned out\n", get_time(coder->start), coder->id);
	pthread_mutex_unlock(&stop_sign);
	return ((void *)0);
}

void	*burn_out(void *arg)
{
	t_coder		**coders;
	int			i;
	long long	time;
	t_input		*input;

	coders = arg;
	input = coders[0]->values;
	while (1)
	{
		i = 0;
		while (i < input->number_of_coders)
		{
			pthread_mutex_lock(&input->burnout);
			time = get_time(coders[i]->last_compile);
			if (coders[i]->cycles < input->number_of_compiles_required)
			{
				if (time > coders[i]->values->time_to_burnout)
					return (ret(coders[i]));
			}
			pthread_mutex_unlock(&input->burnout);
			i++;
		}
	}
	return ((void *)1);
}

void	make_coders(t_coder **coders, t_dongle **dongles, long long start)
{
	int		i;
	t_input	*input;

	i = 0;
	input = coders[0]->values;
	while (i < input->number_of_coders)
	{
		coders[i]->left = dongles[i];
		coders[i]->right = dongles[(i + 1) % input->number_of_coders];
		i++;
	}
	i = 0;
	while (i < input->number_of_coders)
	{
		coders[i]->start = start;
		pthread_create(&coders[i]->thread, NULL, run_coder, coders[i]);
		i++;
	}
}
