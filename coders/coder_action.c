/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:13:33 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/28 12:55:58 by otahiri-         ###   ########.fr       */
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
	{
		release_dongle(coder);
		return ;
	}
	print_log(coder, " is compiling", coder->input);
	ft_usleep(coder->input->time_to_compile, coder);
	release_dongle(coder);
}

void	refactor(t_coder *coder)
{
	if (check_switch(coder->flag))
		return ;
	print_log(coder, " is refactoring", coder->input);
	ft_usleep(coder->input->time_to_refactor, coder);
}

void	debug(t_coder *coder)
{
	if (check_switch(coder->flag))
		return ;
	print_log(coder, " is debugging", coder->input);
	ft_usleep(coder->input->time_to_debug, coder);
}

void	*run_stages(void *args)
{
	t_coder	*coder;

	coder = args;
	while (!check_thread_creation(coder))
		usleep(1000);
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
		usleep(1000);
	}
	return (NULL);
}
