/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 08:14:36 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/04 11:45:27 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(long time_stamp)
{
	struct timeval	tv;
	int				res;

	res = gettimeofday(&tv, NULL);
	if (res)
		return (-1);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time_stamp);
}

void	compile(t_coder *coder)
{
	pthread_mutex_t	lock;
	long			time;

	pthread_mutex_init(&lock, NULL);
	pthread_mutex_lock(&lock);
	acquire_dongle(coder->left, coder);
	acquire_dongle(coder->right, coder);
	time = get_time(coder->input->start);
	if (time == -1)
	{
		pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
		coder->input->kill_switch->kill_switch = 1;
		pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
		return ;
	}

	printf("%ld %d is compiling\n", time, coder->id);
	ft_usleep(coder->input->time_to_compile * 1000);
	release_dongle(coder->left, coder->input);
	release_dongle(coder->right, coder->input);
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
}

void	refactor(t_coder *coder)
{
	long			time;

	time = get_time(coder->input->start);
	if (time == -1)
	{
		pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
		coder->input->kill_switch->kill_switch = 1;
		pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
		return ;
	}
	printf("%ld %d is refactoring\n", time, coder->id);
	ft_usleep(coder->input->time_to_refactor * 1000);
}

void	debug(t_coder *coder)
{
	long			time;

	time = get_time(coder->input->start);
	if (time == -1)
	{
		pthread_mutex_lock(&coder->input->kill_switch->switch_lock);
		coder->input->kill_switch->kill_switch = 1;
		pthread_mutex_unlock(&coder->input->kill_switch->switch_lock);
		return ;
	}
	printf("%ld %d is debugging\n", time, coder->id);
	ft_usleep(coder->input->time_to_debug * 1000);
}
