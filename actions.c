/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:18:09 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/06 13:03:35 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

void	compile(t_coder *coder)
{
	if (coder->values->stop)
		return ;
	aquire_dongles(coder);
	printf("%lld %d is compiling\n", get_time(coder->start), coder->id);
	usleep(coder->values->time_to_compile * 1000);
	release_dongles(coder);
	coder->left->cooldown = coder->values->dongle_cooldown;
	coder->right->cooldown = coder->values->dongle_cooldown;
}

void	debug(t_coder *coder)
{
	t_input		*input;
	long long	time;

	if (coder->values->stop)
		return ;
	time = get_time(coder->start);
	input = coder->values;
	printf("%lld %d is debugging\n", time, coder->id);
	usleep(input->time_to_debug * 1000);
}

void	refactor(t_coder *coder)
{
	t_input		*input;
	long long	time;

	if (coder->values->stop)
		return ;
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
	void		*burn_sign;

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
	pthread_create(&burn_timer, NULL, burn_out, coders);
	pthread_join(burn_timer, &burn_sign);
	if (!(long)burn_sign)
	{
		return (free_all(coders, input, dongles, input->number_of_coders));
	}
	i = 0;
	while (i < input->number_of_coders)
		pthread_join(coders[i++]->thread, NULL);
	return (free_all(coders, input, dongles, input->number_of_coders));
}
