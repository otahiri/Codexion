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
#include <stdio.h>

void	*compile(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	printf("%ld %d is compiling\n", get_time(coder->start), coder->id);
	usleep(input->time_to_compile);
	return (NULL);
}

void	*debug(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	printf("%ld %d is debuggin\n", get_time(coder->start), coder->id);
	usleep(input->time_to_debug);
	return (NULL);
}

void	refactor(t_coder *coder)
{
	t_input	*input;

	input = coder->values;
	printf("%ld %d is refactoring\n", get_time(coder->start),
		coder->id);
	usleep(input->time_to_refactor);
}

void	*run_coder(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	if (!coder->done)
	{
		compile(coder);
		refactor(coder);
		debug(coder);
	}
	return (NULL);
}
