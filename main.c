/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:33:42 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/23 12:46:07 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	burnout(t_coder *coder, t_input *input)
{
	usleep(input->time_to_burnout);
	return (1);
}

void	compile(t_coder coder)
{
	return ;
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_coder	*coder;

	if (argc != 9)
		return (1);
	input = parse(argv);
	if (!input)
		return (0);
	coder = malloc(sizeof(t_coder));
}
