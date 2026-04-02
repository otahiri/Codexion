/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:31:06 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 13:22:44 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"



int	ft_is_digit(char *num)
{
	while (*num)
	{
		if (*num < '0' || *num > '9')
			return (0);
		num++;
	}
	return (1);
}

int	is_input_valid(void *argv[])
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!ft_is_digit(argv[i]))
			return (0);
		i++;
	}
	if (strcmp("fifo", argv[8]) || strcmp("edf", argv[8]))
		return (0);
	return (1);
}

t_input	*parse_input(void **argv)
{
	int		i;
	t_input	*input;

	if (!is_input_valid(argv))
		return (NULL);
	input = malloc(sizeof(t_input));
	i = 0;
	while ()
	return (input);
}
