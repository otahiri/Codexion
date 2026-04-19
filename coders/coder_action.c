/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:13:33 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/19 11:26:05 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

void	compile(t_coder *coder)
{
	aquire_dongles(coder);
	printf("%ld %d is compiling\n", get_time(coder->input->start, coder->input),
		coder->id);
	ft_usleep(coder->input->time_to_compile, coder);
	release_dongle(coder);
}

void	*run_stages(void *args)
{
	t_input			*input;
	t_coder			*coder;
	int				id;
	pthread_mutex_t	lock;

	coder = args;
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	input = coder->input;
	id = coder->id;
	pthread_mutex_unlock(&lock);
	if (!(id % 2))
		usleep(1000);
	while (coder->compiles_done < input->number_of_compiles_required)
	{
		compile(coder);
		coder->compiles_done++;
	}
	pthread_mutex_destroy(&lock);
	return (NULL);
}
