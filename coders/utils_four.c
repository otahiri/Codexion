/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:54:11 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/30 11:54:20 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

void	init_value(t_heap *heap, t_input *input)
{
	int	i;

	i = 0;
	heap->size = 0;
	while (i <= input->number_of_coders)
		heap->coders[i++] = NULL;
}

void	wait_to_start(t_coder *coder)
{
	pthread_mutex_lock(&coder->input->start_thread->mutex);
	while (!coder->input->start_ready)
		pthread_cond_wait(&coder->input->start_thread->cond,
			&coder->input->start_thread->mutex);
	pthread_mutex_unlock(&coder->input->start_thread->mutex);
}

void	set_nums(t_input *input, char **argv)
{
	input->number_of_coders = ft_atoi(argv[1]);
	input->time_to_burnout = ft_atoi(argv[2]);
	input->time_to_compile = ft_atoi(argv[3]);
	input->time_to_debug = ft_atoi(argv[4]);
	input->time_to_refactor = ft_atoi(argv[5]);
	input->number_of_compiles_required = ft_atoi(argv[6]);
	input->dongle_cooldown = ft_atoi(argv[7]);
	input->kill = 0;
	input->start_ready = 0;
}
