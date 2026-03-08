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
	return (NULL);
}

int	check_burnout(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	if (coder->last_compile != -1
		&& get_time(coder->last_compile) > input->time_to_burnout)
	{
		pthread_mutex_unlock(&input->burnout);
		return (1);
	}
	return (0);
}

void	*burn_out(void *arg)
{
	t_coder	**coders;
	int		i;
	int		count;

	coders = arg;
	while (1)
	{
		count = 0;
		i = 0;
		while (i < coders[0]->values->number_of_coders)
		{
			pthread_mutex_lock(&coders[0]->values->burnout);
			if (coders[i]->cycles < coders[0]->values->number_of_compiles_required)
				count++;
			if (check_burnout(coders[i]))
				return (ret(coders[i]));
			pthread_mutex_unlock(&coders[0]->values->burnout);
			i++;
		}
		if (count == coders[0]->values->number_of_coders)
			return (NULL);
		usleep(1000);
	}
	return (NULL);
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
		coders[i]->start = start;
		coders[i]->last_compile = start;
		pthread_create(&coders[i]->thread, NULL, run_coder, coders[i]);
		i++;
	}
}
