/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:18:09 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/04 14:15:02 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

void	compile(t_coder *coder)
{
	while (coder->left->cooldown > get_time(coder->start)
		&& coder->right->cooldown > get_time(coder->start))
		usleep(coder->left->cooldown * 1000);
	lock_dongles(coder);
	printf("%lld %d is compiling\n", get_time(coder->start), coder->id);
	usleep(coder->values->time_to_compile * 1000);
	pthread_mutex_unlock(&coder->right->dongle);
	pthread_mutex_unlock(&coder->left->dongle);
	coder->left->cooldown = coder->values->dongle_cooldown;
	coder->right->cooldown = coder->values->dongle_cooldown;
}

void	debug(t_coder *coder)
{
	t_input		*input;
	long long	time;

	time = get_time(coder->start);
	input = coder->values;
	printf("%lld %d is debugging\n", time, coder->id);
	usleep(input->time_to_debug * 1000);
}

void	refactor(t_coder *coder)
{
	t_input		*input;
	long long	time;

	time = get_time(coder->start);
	input = coder->values;
	printf("%lld %d is refactoring\n", get_time(coder->start), coder->id);
	usleep(input->time_to_refactor * 1000);
}

void	*run_coder(void *arg)
{
	t_coder	*coder;
	int		count;

	count = 0;
	coder = (t_coder *)arg;
	while (coder->cycles < coder->values->number_of_compiles_required)
	{
		compile(coder);
		refactor(coder);
		debug(coder);
		coder->cycles++;
	}
	return (NULL);
}

int	make_threads(t_coder **coders, t_dongle **dongles, t_input *input,
		long long start)
{
	int			i;
	pthread_t	burn_timer;

	i = 0;
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
	i = 0;
	while (i < input->number_of_coders)
		pthread_join(coders[i++]->thread, NULL);
	pthread_create(&burn_timer, NULL, burn_out, coders);
	return (free_all(coders, input, dongles, input->number_of_coders));
}
