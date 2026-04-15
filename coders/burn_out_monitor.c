/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burn_out_monitor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:01:14 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/10 14:49:35 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

static void	wake_up_coders(t_coder **coders)
{
	int		i;
	t_input	*input;

	i = 0;
	input = coders[0]->input;
	while (i < input->coders_count)
	{
		pthread_cond_broadcast(&coders[i]->sleep->cond);
		pthread_cond_signal(&coders[i]->sleep->cond);
		i++;
	}
}

static int	check_coders_done(t_coder **coders, pthread_mutex_t lock)
{
	int		i;
	t_input	*input;

	input = coders[0]->input;
	i = 0;
	while (i < input->coders_count)
	{
		pthread_mutex_lock(&lock);
		if (coders[i]->compile_count >= input->number_of_compiles_required)
		{
			pthread_mutex_unlock(&lock);
			return (1);
		}
		pthread_mutex_unlock(&lock);
		i++;
	}
	return (0);
}

static int	check_coders_burnout(t_coder **coders, pthread_mutex_t lock)
{
	int		i;
	t_input	*input;

	input = coders[0]->input;
	i = 0;
	while (i < input->coders_count)
	{
		pthread_mutex_lock(&lock);
		if (coders[i]->compile_count < input->number_of_compiles_required
			&& (coders[i]->last_compile + input->time_to_burnout <= get_time(0,
					input)))
		{
			activate_switch(input, ft_strcat(ft_itoa(coders[i]->id),
					"burned out\n"));
			wake_up_coders(coders);
			break ;
		}
		pthread_mutex_unlock(&lock);
		i++;
	}
	pthread_mutex_unlock(&lock);
	return (0);
}

void	*monitoring(void *arg)
{
	t_coder			**coders;
	t_input			*input;
	pthread_mutex_t	lock;

	coders = arg;
	input = coders[0]->input;
	pthread_mutex_init(&lock, NULL);
	while (1)
	{
		if (check_coders_done(coders, lock) || check_coders_burnout(coders,
				lock))
		{
			break ;
		}
		usleep(1000);
	}
	if (check_switch(input))
	{
		printf("%s", input->kill_switch->dialogue);
		free(input->kill_switch->dialogue);
	}
	pthread_mutex_destroy(&lock);
	return (NULL);
}
