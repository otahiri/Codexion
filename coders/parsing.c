/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:14:01 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 10:14:20 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

static int	validate_args(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (!is_valid_number(argv[i]))
			return (0);
		i++;
	}
	if ((strcmp("fifo", argv[8]) && strcmp("edf", argv[8])))
		return (0);
	return (1);
}

static int	is_input_valid(t_input *input)
{
	if (input->number_of_coders < 0 || input->time_to_burnout < 0
		|| input->time_to_compile < 0 || input->time_to_debug < 0
		|| input->time_to_refactor < 0 || input->number_of_compiles_required < 0
		|| input->dongle_cooldown < 0)
		return (0);
	return (1);
}

t_input	*parse_input(char **argv, int argc)
{
	t_input	*input;

	if (argc != 9 || !validate_args(argv))
		return (NULL);
	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	input->number_of_coders = ft_atoi(argv[1]);
	input->time_to_burnout = ft_atoi(argv[2]);
	input->time_to_compile = ft_atoi(argv[3]);
	input->time_to_debug = ft_atoi(argv[4]);
	input->time_to_refactor = ft_atoi(argv[5]);
	input->number_of_compiles_required = ft_atoi(argv[6]);
	input->dongle_cooldown = ft_atoi(argv[7]);
	input->scheduler = ft_strdup(argv[8]);
	input->write_lock = create_mutex();
	if (!is_input_valid(input) || !input->write_lock)
	{
		free(input);
		return (NULL);
	}
	return (input);
}
