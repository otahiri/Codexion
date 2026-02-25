/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 10:11:12 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/24 13:38:19 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"
#include <string.h>

int	ft_isalpha(char *str)
{
	while (str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (0);
}

t_input	*parse(char **argv)
{
	t_input	*input;
	int		i;

	i = 1;
	while (i < 8)
	{
		if (!ft_isalpha(argv[i]))
		{
			return (NULL);
		}
		i++;
	}
	input = malloc(sizeof(t_input));
	input->number_of_coders = atoi(argv[1]);
	input->time_to_burnout = atoi(argv[2]);
	input->time_to_compile = atoi(argv[3]);
	input->time_to_debug = atoi(argv[4]);
	input->time_to_refactor = atoi(argv[5]);
	input->number_of_compiles_required = atoi(argv[6]);
	input->dongle_cooldown = atoi(argv[7]);
	input->scheduler = argv[8];
	if (strcmp(input->scheduler, "fifo") && strcmp(input->scheduler, "edf"))
		return (free(input), NULL);
	return (input);
}
