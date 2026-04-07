/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:06:00 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/04 11:10:00 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_dongle	*create_dongle(t_input *input)
{
	t_dongle	*dongle;

	dongle = malloc(sizeof(t_dongle));
	dongle->down_time = input->dongle_cooldown;
	dongle->cooldown = 0;
	dongle->lock = malloc(sizeof(t_mutex));
	pthread_mutex_init(&dongle->lock->mutex, NULL);
	pthread_cond_init(&dongle->lock->cond, NULL);
	dongle->heap = create_heap(input);
	dongle->next_availabe = get_time(0);
	return (dongle);
}

static t_coder	**initialize_coders(t_input *input)
{
	t_coder	**coders;
	int		i;

	i = 0;
	coders = malloc(sizeof(t_coder *));
	while (i < input->coders_count)
	{
		coders[i] = malloc(sizeof(t_coder));
		coders[i]->id = i + 1;
		coders[i]->input = input;
		coders[i]->compile_count = 0;
		coders[i]->right = create_dongle(input);
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

	if (argc != 9)
		return (0);
	input = parse_input(argv);
	if (!input)
		return (0);
	coders = initialize_coders(input);
	input->start = get_time(0);
	run_coders(coders, input);
	return (0);
}
