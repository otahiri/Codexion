/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 12:49:41 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/28 13:24:40 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	extra_for_sim(t_coder **coders, t_input *input, t_flag *flag)
{
	int	i;

	i = 0;
	input->start = get_time(0, input);
	while (coders[i])
		coders[i++]->flag = flag;
}

int	join_thread(t_coder **coders, int current, t_input *input)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&input->write_lock->mutex);
	input->kill++;
	pthread_mutex_unlock(&input->write_lock->mutex);
	while (i < current)
		pthread_join(coders[i++]->thread, NULL);
	return (0);
}

int	check_program_end(t_coder *coder)
{
	pthread_mutex_lock(&coder->input->write_lock->mutex);
	if (coder->input->kill)
	{
		pthread_mutex_unlock(&coder->input->write_lock->mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->input->write_lock->mutex);
	return (0);
}
