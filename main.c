/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:33:42 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/25 12:14:14 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

void	*compile(void *arg)
{
	t_input	*input;
	t_coder	*coder;

	coder = (t_coder *)arg;
	input = coder->values;
	printf("coder %d is compiling\n", coder->id);
	usleep(input->time_to_compile);
	return (NULL);
}

void	*debug(void *arg)
{
	t_input	*input;
	t_coder	*coder;

	coder = (t_coder *)arg;
	input = coder->values;
	printf("coder %d is debugging\n", coder->id);
	usleep(input->time_to_debug);
	return (NULL);
}

void	*refactor(void *arg)
{
	t_input	*input;
	t_coder	*coder;

	coder = (t_coder *)arg;
	input = coder->values;
	printf("coder %d is refactoring\n", coder->id);
	usleep(input->time_to_refactor);
	return (NULL);
}

t_coder	*make_coder(int id, t_input *value)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	coder->done = false;
	coder->id = id;
	coder->values = value;
	return (coder);
}

int	main(int argc, char **argv)
{
	t_input	*input;
	t_coder	*coder;

	if (argc != 9)
		return (1);
	input = parse(argv);
	coder = make_coder(1, input);
	pthread_create(&coder->thread, NULL, compile(coder), input);
	return (0);
}
