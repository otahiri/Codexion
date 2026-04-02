/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:31:06 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 18:59:04 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	validate_args(char **argv)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!ft_isdigit(argv[i]))
			return (0);
		i++;
	}
	if (strcmp("fifo", argv[8]) || strcmp("edf", argv[8]))
		return (0);
	return (1);
}

static int	is_input_valid(t_input *input)
{
	if (input->coders_count < 0 || input->time_to_burnout < 0
		|| input->time_to_compile < 0 || input->time_to_debug < 0
		|| input->time_to_refactor < 0 || input->compile_count < 0
		|| input->dongle_cooldown)
		return (0);
	return (1);
}

t_input	*parse_input(char **argv)
{
	t_input	*input;

	if (!validate_args(argv))
		return (NULL);
	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->coders_count = ft_atoi(argv[1]);
	input->time_to_burnout = ft_atoi(argv[2]);
	input->time_to_compile = ft_atoi(argv[3]);
	input->time_to_debug = ft_atoi(argv[4]);
	input->time_to_refactor = ft_atoi(argv[5]);
	input->compile_count = ft_atoi(argv[6]);
	input->dongle_cooldown = ft_atoi(argv[7]);
	input->scheduler = argv[8];
	if (!is_input_valid(input))
	{
		free(input);
		return (NULL);
	}
	return (input);
}
