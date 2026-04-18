/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:14:23 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 15:51:43 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

t_coder	**initialize_coders(t_input *input)
{
	t_coder	**coders;
	int		i;

	i = 0;
	coders = malloc(sizeof(t_coder) * input->number_of_coders);
	if (!coders)
		return (NULL);
	while (i < input->number_of_coders)
	{
		coders[i] = create_coder(input, i + 1);
		i++;
	}
	i = 0;
	while (i < input->number_of_coders)
	{
		coders[i]->left = coders[(i + input->number_of_coders + 1)
			% input->number_of_coders]->right;
		i++;
	}
	return (coders);
}

void	start_sim(t_coder **coders, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->number_of_coders)
	{
		pthread_create(&coders[i]->thread, NULL, run_stages, coders[i]);
		i++;
	}
	i = 0;
	while (i < input->number_of_coders)
	{
		pthread_join(coders[i]->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_coder	**coders;
	t_input	*input;

	input = parse_input(argv, argc);
	if (!input)
		return (0);
	input->start = get_time(0, input);
	coders = initialize_coders(input);
	start_sim(coders, input);
}
