/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 08:14:36 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/10 14:41:01 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	compile(t_coder *coder)
{
	long			time;

	acquire_dongle(coder->left, coder);
	acquire_dongle(coder->right, coder);
	time = get_time(coder->input->start, coder->input);
	pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
	if (coder->input->kill_switch->turn_off)
	{
		release_dongle(coder->right, coder->input);
		release_dongle(coder->left, coder->input);
		pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
		return ;
	}
	pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
	printf("%ld %d is compiling\n", time, coder->id);
	ft_usleep(coder->input->time_to_compile * 1000, coder->input);
	coder->last_compile = get_time(0, coder->input);
	release_dongle(coder->right, coder->input);
	release_dongle(coder->left, coder->input);
}

void	refactor(t_coder *coder)
{
	long			time;

	time = get_time(coder->input->start, coder->input);
	pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
	if (coder->input->kill_switch->turn_off)
	{
		pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
		return ;
	}
	pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
	printf("%ld %d is refactoring\n", time, coder->id);
	ft_usleep(coder->input->time_to_refactor * 1000, coder->input);
}

void	debug(t_coder *coder)
{
	long			time;

	time = get_time(coder->input->start, coder->input);
	pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
	if (coder->input->kill_switch->turn_off)
	{
		pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
		return ;
	}
	pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
	printf("%ld %d is debugging\n", time, coder->id);
	ft_usleep(coder->input->time_to_debug * 1000, coder->input);
}
