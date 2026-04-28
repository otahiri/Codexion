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

int	check_thread_creation(t_coder *coder)
{
	pthread_mutex_lock(&coder->input->write_lock->mutex);
	if (coder->input->threds_made == coder->input->number_of_coders + 1)
	{
		pthread_mutex_unlock(&coder->input->write_lock->mutex);
		return (1);
	}
	pthread_mutex_unlock(&coder->input->write_lock->mutex);
	return (0);
}

void	add_thread_created(t_input *input)
{
	pthread_mutex_lock(&input->write_lock->mutex);
	input->threds_made++;
	pthread_mutex_unlock(&input->write_lock->mutex);
}

void	extra_for_sim(t_coder *coder, t_input *input, t_flag *flag)
{
	coder->request = input->start;
	coder->last_compile = input->start;
	coder->flag = flag;
}
