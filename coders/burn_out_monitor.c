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
#include <pthread.h>
#include <stdio.h>

static void	wake_up_coder(t_coder **coders)
{
	int		i;
	t_input	*input;

	i = 0;
	input = coders[0]->input;
	while (i < input->coders_count)
	{
		release_dongle(coders[i]->left, input);
		release_dongle(coders[i]->right, input);
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
		if (coders[i]->compile_count >= input->number_of_compiles_required)
			return (1);
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
		if (coders[i]->compile_count == input->number_of_compiles_required
			&& !(coders[i]->last_compile + input->time_to_burnout > get_time(0,
					input)))
		{
			printf("%ld %d burned out\n", get_time(input->start, input),
				coders[i]->id);
			input->kill_switch->turn_off = 1;
			wake_up_coder(coders);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_coder			**coders;
	t_input			*input;
	pthread_mutex_t	lock;

	coders = arg;
	input = coders[0]->input;
	lock = input->kill_switch->monitoring_lock;
	pthread_mutex_init(&lock, NULL);
	while (1)
	{
		if (check_coders_burnout(coders, lock) || check_coders_done(coders,
				lock))
			break ;
		ft_usleep(1000, input);
	}
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	return (NULL);
}
