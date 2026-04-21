/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burn_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:17:32 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/21 15:01:28 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	wake_up_coders(t_coder **coders)
{
	int		i;
	t_input	*input;

	i = 0;
	input = coders[0]->input;
	while (i < input->number_of_coders)
	{
		pthread_cond_broadcast(&coders[i]->sleep->cond);
		i++;
	}
}

static int	check_coders_done(t_coder **coders, pthread_mutex_t lock)
{
	int		i;
	t_input	*input;

	input = coders[0]->input;
	i = 0;
	while (i < input->number_of_coders)
	{
		pthread_mutex_lock(&lock);
		if (coders[i]->compiles_done >= input->number_of_compiles_required)
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
	t_flag	*flag;
	t_input	*input;

	flag = coders[0]->flag;
	input = coders[0]->input;
	i = 0;
	while (i < input->number_of_coders)
	{
		pthread_mutex_lock(&lock);
		if (coders[i]->compiles_done < input->number_of_compiles_required
			&& (coders[i]->last_compile + input->time_to_burnout <= get_time(0,
					input)))
		{
			activate_switch(flag, ft_strcat(ft_itoa(coders[i]->id),
					" burned out\n"));
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
	t_coder	**coders;
	t_input	*input;
	t_flag	*flag;

	coders = arg;
	input = coders[0]->input;
	flag = coders[0]->flag;
	while (1)
	{
		if (check_coders_done(coders, flag->lock->mutex)
			|| check_coders_burnout(coders, flag->lock->mutex))
			break ;
		usleep(1000);
	}
	if (check_switch(flag))
		printf("%s", flag->dialogue);
	return (NULL);
}
