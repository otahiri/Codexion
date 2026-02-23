/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:11:12 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/23 10:15:00 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

t_input	*parse(char **argv)
{
	t_input	*input;

	input = malloc(sizeof(t_input));
	input->number_of_coders = atoi(argv[1]);
	input->time_to_burnout = atoi(argv[2]);
	input->time_to_compile = atoi(argv[3]);
	input->time_to_debug = atoi(argv[4]);
	input->time_to_refactor = atoi(argv[5]);
	input->number_of_compiles_required = atoi(argv[6]);
	input->dongle_cooldown = atoi(argv[7]);
	input->scheduler = atoi(argv[8]);
	if (!input->number_of_coders || !input->time_to_burnout
		|| !input->time_to_compile || !input->time_to_debug
		|| !input->time_to_refactor || !input->number_of_compiles_required
		|| !input->dongle_cooldown || !input->scheduler)
	{
		return (NULL);
	}
	return (input);
}
