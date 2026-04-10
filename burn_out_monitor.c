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
#include <bits/pthreadtypes.h>
#include <pthread.h>
#include <unistd.h>

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

static int	check_coders(t_coder **coders)
{
	int	i;
	t_input	*input;

	input = coders[0]->input;
	i = 0;
	while (i < input->coders_count)
	{
		if (coders[i]->compile_count < input->number_of_compiles_required)
			return (0);
		i++;
	}
	return (1);
}

void	*monitoring(void *arg)
{
	t_coder	**coders;
	t_input	*input;
	int		i;
	pthread_mutex_t	lock;

	coders = arg;
	input = coders[0]->input;
	pthread_mutex_init(&lock, NULL);
	printf("%d is the check for the input existance\n", input->coders_count);
	while (1)
	{
		i = 0;
		while (i < input->coders_count)
		{
			pthread_mutex_lock(&lock);
			if (coders[i]->compile_count == input->number_of_compiles_required && coders[i]->last_compile + input->time_to_burnout <= get_time(0, input))
			{
				printf("%ld %d burned out\n", get_time(input->start, input),
					coders[i]->id);
				input->kill_switch->kill_switch = 1;
				wake_up_coder(coders);
				pthread_mutex_unlock(&lock);
				pthread_mutex_destroy(&lock);
				return (NULL);
			}
			pthread_mutex_unlock(&lock);
			i++;
			usleep(1000);
		}
		if (check_coders(coders))
			break ;
	}
	pthread_mutex_unlock(&lock);
	pthread_mutex_destroy(&lock);
	return (NULL);
}
