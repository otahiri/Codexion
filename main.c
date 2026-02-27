/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:33:42 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/27 12:14:41 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

t_coder	*make_coder(int id, long start, t_input *value)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	coder->done = false;
	coder->id = id;
	coder->values = value;
	coder->start = start;
	return (coder);
}

int	main(int argc, char **argv)
{
	t_input			*input;
	t_coder			*coder;
	struct timeval	tv;
	long			start;

	gettimeofday(&tv, NULL);
	start = tv.tv_usec;
	printf("%ld\n", get_time(start));
	usleep(900);
	printf("%ld\n", get_time(start));
	if (argc != 9)
		return (1);
	input = parse(argv);
	coder = make_coder(1, start, input);
	pthread_create(&coder->thread, NULL, run_coder, coder);
	pthread_join(coder->thread, NULL);
	return (0);
}
