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

static int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

static int	ft_atoi(char *nptr)
{
	long	num;

	num = 0;
	while (*nptr && (*nptr == ' ' || ((*nptr <= '\r' && *nptr >= '\t'))))
		nptr++;
	if (*nptr && (*nptr == '+'))
		nptr++;
	while (*nptr && (*nptr >= '0' && *nptr <= '9'))
	{
		if (((num * 10) + (*nptr - '0')) < 0)
			return (-1);
		num *= 10;
		num += *nptr - '0';
		nptr++;
	}
	if (!ft_isdigit(nptr) || num > 2147483647)
		return (-1);
	return (num);
}

static t_input	*ft_valid(t_input **input)
{
	if ((strcmp((*input)->scheduler, "fifo") && strcmp((*input)->scheduler,
				"edf")) || (*input)->number_of_coders <= 0
		|| (*input)->number_of_compiles_required <= 0
		|| (*input)->time_to_burnout < 0 || (*input)->time_to_compile < 0
		|| (*input)->time_to_debug < 0 || (*input)->time_to_refactor < 0
		|| (*input)->dongle_cooldown < 0)
	{
		free((*input));
		input = NULL;
		return (NULL);
	}
	return ((*input));
}

void	alloc_dongles(int count, t_input *input)
{
	int	i;

	i = 0;
	input->dongles = malloc(sizeof(pthread_mutex_t) * count);
	while (i < count)
		pthread_mutex_init(&(input->dongles[i++]), NULL);
}

t_input	*parse(char **argv)
{
	t_input	*input;
	int		i;

	i = 1;
	while (i < 8)
	{
		if (!ft_isdigit(argv[i]) || strlen(argv[i]) > 10 || argv[i][0] == '-')
			return (NULL);
		i++;
	}
	input = malloc(sizeof(t_input));
	input->number_of_coders = ft_atoi(argv[1]);
	input->time_to_burnout = ft_atoi(argv[2]);
	input->time_to_compile = ft_atoi(argv[3]);
	input->time_to_debug = ft_atoi(argv[4]);
	input->time_to_refactor = ft_atoi(argv[5]);
	input->number_of_compiles_required = ft_atoi(argv[6]);
	input->dongle_cooldown = ft_atoi(argv[7]);
	input->scheduler = argv[8];
	alloc_dongles(input->number_of_coders, input);
	return (ft_valid(&input));
}
