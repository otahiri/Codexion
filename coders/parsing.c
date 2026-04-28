/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:14:01 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/28 13:18:44 by otahiri-         ###   ########.fr       */
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

static void	*print_invalid(void)
{
	printf("invalid input usage example ./codexion number_of_coders\
time_to_burnout time_to_compile time_to_debug time_to_refactor \
number_of_compiles_required dongle_cooldown scheduler\n ");
	return (NULL);
}

static int	is_input_valid(t_input *input)
{
	if (input->number_of_coders <= 0 || input->time_to_burnout < 0
		|| input->time_to_compile < 0 || input->time_to_debug < 0
		|| input->time_to_refactor < 0
		|| input->number_of_compiles_required < 0
		|| input->dongle_cooldown < 0)
		return (0);
	return (1);
}

void	set_nums(t_input *input, char **argv)
{
	input->number_of_coders = ft_atoi(argv[1]);
	input->time_to_burnout = ft_atoi(argv[2]);
	input->time_to_compile = ft_atoi(argv[3]);
	input->time_to_debug = ft_atoi(argv[4]);
	input->time_to_refactor = ft_atoi(argv[5]);
	input->number_of_compiles_required = ft_atoi(argv[6]);
	input->dongle_cooldown = ft_atoi(argv[7]);
	input->threds_made = 0;
}

t_input	*parse_input(char **argv, int argc)
{
	t_input	*input;

	if (argc != 9 || !validate_args(argv))
		return (print_invalid());
	input = malloc(sizeof(t_input));
	if (!input)
		return (NULL);
	set_nums(input, argv);
	input->scheduler = ft_strdup(argv[8]);
	if (!input->scheduler)
	{
		free(input);
		return (NULL);
	}
	input->write_lock = create_mutex();
	if (!is_input_valid(input) || !input->write_lock)
	{
		free(input->scheduler);
		free_mutex(input->write_lock);
		free(input);
		return (print_invalid());
	}
	return (input);
}
