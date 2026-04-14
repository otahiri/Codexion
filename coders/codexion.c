/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:06:00 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/10 10:41:08 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

void	*free_all(t_coder **coders, t_input *input)
{
	int		i;

	i = 0;
	while (i < input->coders_count && coders)
	{
		free(coders[i]->right->heap->coders);
		free(coders[i]->right->heap);
		free(coders[i]->right->lock);
		free(coders[i]->right);
		free(coders[i]->sleep);
		free(coders[i]);
		i++;
	}
	if (coders)
		free(coders);
	free(input->kill_switch);
	free(input);
	return (NULL);
}

static t_dongle	*create_dongle(t_input *input)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	if (!dongle)
		return (NULL);
	dongle->down_time = input->dongle_cooldown;
	dongle->cooldown = 1;
	dongle->lock = malloc(sizeof(t_mutex));
	if (!dongle->lock)
	{
		free(dongle);
		return (NULL);
	}
	pthread_mutex_init(&dongle->lock->mutex, NULL);
	pthread_cond_init(&dongle->lock->cond, NULL);
	dongle->heap = create_heap(input);
	if (!dongle->heap)
	{
		free(dongle->lock);
		free(dongle);
		return (NULL);
	}
	dongle->next_availabe = get_time(0, input);
	return (dongle);
}

static	t_coder	*coder_setup( t_input *input)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	coder->input = input;
	coder->compile_count = 0;
	coder->right = create_dongle(input);
	if (!coder->right)
	{
		free(coder);
		return (NULL);
	}
	coder->last_compile = get_time(0, input);
	coder->request_time = get_time(0, input);
	coder->sleep = malloc(sizeof(t_mutex));
	pthread_mutex_init(&coder->sleep->mutex, NULL);
	pthread_mutex_init(&coder->lock, NULL);
	return (coder);
}

static t_coder	**initialize_coders(t_input *input)
{
	t_coder	**coders;
	int		i;

	i = 0;
	coders = malloc(sizeof(t_coder *) * input->coders_count);
	if (!coders)
		return (NULL);
	while (i < input->coders_count)
	{
		coders[i] = coder_setup(input);
		if (!coders[i])
			return (free_all(coders, input));
		coders[i]->id = i + 1;
		i++;
	}
	i = 0;
	while (i < input->coders_count)
	{
		coders[i]->left = coders[(i + 1 + input->coders_count)
			% input->coders_count]->right;
		i++;
	}
	return (coders);
}

int	main(int argc, char *argv[])
{
	t_input	*input;
	t_coder	**coders;

	input = parse_input(argv, argc);
	if (!input)
		return (0);
	coders = initialize_coders(input);
	if (!coders)
	{
		free(input);
		return (0);
	}
	input->start = get_time(0, input);
	input->kill_switch = malloc(sizeof(t_off));
	if (!input->kill_switch)
	{
		free_all(coders, input);
		return (0);
	}
	input->kill_switch->turn_off = 0;
	pthread_mutex_init(&input->kill_switch->switch_lock, NULL);
	run_coders(coders, input);
	free_all(coders, input);
	return (0);
}
