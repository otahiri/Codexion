/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burn_monitor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:17:32 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/21 18:06:47 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

static void	wake_up_coders(t_coder **coders)
{
	int		i;
	t_input	*input;

	i = 0;
	input = coders[0]->input;
	while (coders[i])
	{
		pthread_mutex_lock(&coders[i]->sleep->mutex);
		pthread_cond_broadcast(&coders[i]->sleep->cond);
		pthread_mutex_unlock(&coders[i]->sleep->mutex);
		pthread_mutex_lock(&coders[i]->right->lock->mutex);
		pthread_cond_broadcast(&coders[i]->right->lock->cond);
		pthread_mutex_unlock(&coders[i]->right->lock->mutex);
		pthread_mutex_lock(&coders[i]->left->lock->mutex);
		pthread_cond_broadcast(&coders[i]->left->lock->cond);
		pthread_mutex_unlock(&coders[i]->left->lock->mutex);
		i++;
	}
}

static int	check_coders_done(t_coder **coders)
{
	int		i;
	t_input	*input;
	t_flag	*flag;
	int		compile_count;

	input = coders[0]->input;
	flag = coders[0]->flag;
	i = 0;
	while (coders[i])
	{
		pthread_mutex_lock(&coders[i]->lock->mutex);
		compile_count = coders[i]->compiles_done;
		pthread_mutex_unlock(&coders[i]->lock->mutex);
		pthread_mutex_lock(&flag->lock->mutex);
		if (compile_count < input->number_of_compiles_required)
		{
			pthread_mutex_unlock(&flag->lock->mutex);
			return (0);
		}
		pthread_mutex_unlock(&flag->lock->mutex);
		i++;
	}
	return (1);
}

static int	check_coders_burnout(t_coder **coders)
{
	int		i;
	t_input	*input;
	long	last_compile;
	int		compile_count;

	input = coders[0]->input;
	i = 0;
	while (coders[i])
	{
		pthread_mutex_lock(&coders[i]->lock->mutex);
		last_compile = coders[i]->last_compile;
		compile_count = coders[i]->compiles_done;
		pthread_mutex_unlock(&coders[i]->lock->mutex);
		if (compile_count < input->number_of_compiles_required && (last_compile
				+ input->time_to_burnout < get_time(0, input)))
		{
			activate_switch(coders[i]->flag, ft_strdup(" has burned out"));
			coders[i]->flag->coder_idx = i;
			wake_up_coders(coders);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_coder	**coders;
	t_flag	*flag;

	coders = arg;
	flag = coders[0]->flag;
	while (1)
	{
		if (check_coders_done(coders) || check_coders_burnout(coders))
			break ;
		usleep(1000);
	}
	if (check_switch(flag))
		print_log(coders[flag->coder_idx], flag->dialogue, coders[0]->input);
	return (NULL);
}
