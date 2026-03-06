/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:33:42 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/06 12:57:23 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	free_all(t_coder **coders, t_input *input, t_dongle **dongles, int count)
{
	int	i;

	i = 0;
	if (input)
		free(input);
	if (dongles)
	{
		while (i < count)
		{
			pthread_mutex_destroy(&dongles[i]->dongle);
			pthread_cond_destroy(&dongles[i++]->cond_var);
		}
		free(dongles);
	}
	if (coders)
	{
		while (i < count)
		{
			free(coders[i++]);
		}
		free(coders);
	}
	return (0);
}

t_coder	**make_coder(t_input *input)
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
			free_all(coders, NULL, NULL, i);
			return (NULL);
		}
		coders[i]->last_compile = get_time(0);
		coders[i]->cycles = 0;
		coders[i]->id = i + 1;
		coders[i]->values = input;
		i++;
	}
	return (coders);
}

t_dongle	**make_dongles(int count)
{
	t_dongle	**dongles;
	int			i;

	i = 0;
	dongles = malloc(sizeof(t_dongle *) * count);
	if (!dongles)
		return (NULL);
	while (i < count)
	{
		dongles[i] = malloc(sizeof(t_dongle));
		dongles[i]->cooldown = 0;
		dongles[i]->in_use = false;
		dongles[i]->heap = malloc(sizeof(void *) * 2);
		dongles[i]->heap[0] = NULL;
		dongles[i]->heap[1] = NULL;
		pthread_mutex_init(&dongles[i]->dongle, NULL);
		pthread_cond_init(&dongles[i]->cond_var, NULL);
		dongles[i]->heap_size = 0;
		i++;
	}
	return (dongles);
}

int	main(int argc, char **argv)
{
	t_coder		**coders;
	t_input		*input;
	t_dongle	**dongles;

	if (argc != 9)
		return (1);
	input = parse(argv);
	coders = make_coder(input);
	if (!coders)
		return (free_all(NULL, input, NULL, input->number_of_coders));
	dongles = make_dongles(input->number_of_coders);
	if (!dongles)
		return (free_all(coders, input, NULL, input->number_of_coders));
	return (make_threads(coders, dongles, input, get_time(0)));
}
