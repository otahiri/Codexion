/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 10:18:09 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/27 12:21:23 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>

void	compile(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	printf("%ld %d is compiling\n", get_time(coder->start), coder->id);
	usleep(input->time_to_compile);
}

void	debug(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	printf("%ld %d is debuggin\n", get_time(coder->start), coder->id);
	usleep(input->time_to_debug);
}

void	refactor(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	printf("%ld %d is refactoring\n", get_time(coder->start), coder->id);
	usleep(input->time_to_refactor);
}

void	*run_coder(void *arg)
{
	t_coder			*coder;
	pthread_mutex_t	wait;

	pthread_mutex_lock(&wait);
	pthread_mutex_unlock(&wait);
	coder = (t_coder *)arg;
	while (!coder->done)
	{
		compile(coder);
		refactor(coder);
		debug(coder);
		coder->done = 1;
	}
	return (NULL);
}
