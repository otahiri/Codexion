/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:13:33 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/21 17:52:03 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <unistd.h>

void	compile(t_coder *coder)
{
	aquire_dongles(coder);
	pthread_mutex_lock(&coder->lock->mutex);
	coder->last_compile = get_time(0, coder->input);
	pthread_mutex_unlock(&coder->lock->mutex);
	if (check_switch(coder->flag))
		return ;
	printf("%ld %d is compiling\n", get_time(coder->input->start, coder->input),
		coder->id);
	ft_usleep(coder->input->time_to_compile, coder);
	release_dongle(coder);
}

void	refactor(t_coder *coder)
{
	if (check_switch(coder->flag))
		return ;
	printf("%ld %d is refactoring\n", get_time(coder->input->start,
			coder->input), coder->id);
	ft_usleep(coder->input->time_to_refactor, coder);
}

void	debug(t_coder *coder)
{
	if (check_switch(coder->flag))
		return ;
	printf("%ld %d is debugging\n", get_time(coder->input->start,
			coder->input), coder->id);
	ft_usleep(coder->input->time_to_debug, coder);
}

void	*run_stages(void *args)
{
	t_coder	*coder;

	coder = args;
	if ((coder->id % 2))
		usleep(1000);
	while (coder->compiles_done < coder->input->number_of_compiles_required)
	{
		compile(coder);
		if (check_switch(coder->flag))
			return (NULL);
		debug(coder);
		if (check_switch(coder->flag))
			return (NULL);
		refactor(coder);
		if (check_switch(coder->flag))
			return (NULL);
		pthread_mutex_lock(&coder->lock->mutex);
		coder->compiles_done++;
		pthread_mutex_unlock(&coder->lock->mutex);
	}
	return (NULL);
}
