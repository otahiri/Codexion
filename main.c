/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:33:42 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/27 12:14:41 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

long	get_start_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000);
}

int	free_all(t_coder **coders, t_input *input, int count)
{
	int				i;

	i = 0;
	if (input)
		free(input);
	if (coders)
	{
		while (i < count)
		{
			pthread_mutex_destroy(&input->dongles[i]);
			free(coders[i++]);
		}
		free(coders);
	}
	free(input->dongles);
	return (0);
}

t_coder	**make_coder(long start, t_input *input)
{
	t_coder	**coders;
	int		i;

	i = 0;
	if (!input)
		return (NULL);
	coders = malloc(sizeof(t_coder *) * input->number_of_coders);
	if (!coders)
		return (NULL);
	while (i < input->number_of_coders)
	{
		coders[i] = malloc(sizeof(t_coder));
		if (!coders[i])
		{
			free_all(coders, NULL, i);
			return (NULL);
		}
		coders[i]->done = false;
		coders[i]->id = i + 1;
		coders[i]->start = start;
		coders[i]->values = input;
		i++;
	}
	return (coders);
}

int	main(int argc, char **argv)
{
	t_coder	**coders;
	t_input	*input;
	long	start;
	int		i;

	i = 0;
	start = get_start_time();
	if (argc != 9)
		return (1);
	input = parse(argv);
	coders = make_coder(start, input);
	if (!coders)
		return (free_all(NULL, input, input->number_of_coders));
	while (coders[i])
	{
		pthread_create(&coders[i]->thread, NULL, run_coder, coders[i]);
		i++;
	}
	i = 0;
	while (coders[i])
		pthread_join(coders[i++]->thread, NULL);
	return (free_all(coders, input, input->number_of_coders));
}
