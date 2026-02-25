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

void	*foo(void *arg)
{
	t_input	*input;

	input = (t_input *)arg;
	printf("Thread is running.\n");
	usleep(input->time_to_compile);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	thread1;
	t_input		*input;

	if (argc != 8)
		return (1);
	input = parse(argv);
	pthread_create(&thread1, NULL, foo, input);
	pthread_join(thread1, NULL);
	return (0);
}
