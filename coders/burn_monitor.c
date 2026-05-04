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

static void	*print_burn_log(t_flag *flag, t_coder *coder)
{
	pthread_mutex_lock(&coder->input->write_lock->mutex);
	printf("%ld %d burned out\n", flag->burn_ts, flag->coder_idx + 1);
	pthread_mutex_unlock(&coder->input->write_lock->mutex);
	return (NULL);
}

static int	check_coders_burnout(t_coder **coders, t_flag *flag)
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
				+ input->time_to_burnout <= get_time(0, input)))
		{
			flag->burn_ts = get_time(input->start, input);
			activate_switch(flag, " burned out");
			coders[i]->flag->coder_idx = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	set_timers(t_coder **coders)
{
	int	i;

	i = 0;
	while (coders[i])
	{
		coders[i]->request = coders[i]->input->start;
		coders[i]->last_compile = coders[i]->input->start;
		i++;
	}
}

void	*monitoring(void *arg)
{
	t_coder	**coders;

	coders = arg;
	pthread_mutex_lock(&coders[0]->input->write_lock->mutex);
	if (coders[0]->input->kill)
	{
		pthread_mutex_unlock(&coders[0]->input->write_lock->mutex);
		return (0);
	}
	pthread_mutex_unlock(&coders[0]->input->write_lock->mutex);
	pthread_mutex_lock(&coders[0]->input->start_thread->mutex);
	coders[0]->input->start = get_time(0, coders[0]->input);
	coders[0]->input->start_ready = 1;
	set_timers(coders);
	pthread_cond_broadcast(&coders[0]->input->start_thread->cond);
	pthread_mutex_unlock(&coders[0]->input->start_thread->mutex);
	while (1)
	{
		if (check_coders_burnout(coders, coders[0]->flag))
			return (print_burn_log(coders[0]->flag, coders[0]));
		if (check_coders_done(coders))
			return (NULL);
		usleep(1000);
	}
}
