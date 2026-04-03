/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:06:00 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 18:51:53 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdlib.h>

t_coder	**initialize_coders(t_input *input)
{
	t_coder	**coders;
	int		i;

	i = 0;
	coders = malloc(sizeof(t_coder *));
	while (i < input->coders_count)
	{
		coders[i] = malloc(sizeof(t_coder));
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
	return (0);
}
