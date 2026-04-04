/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:58:55 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/04 09:53:36 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*run_stages(void *args)
{
	t_coder					*coder;
	static pthread_mutex_t	lock = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&lock);
	coder = args;
	while (coder->compile_count < coder->input->compile_count)
	{
		compile(coder);
		debug(coder);
		refactor(coder);
		coder->compile_count++;
	}
	pthread_mutex_unlock(&lock);
	return (NULL);
}

void	run_coders(t_coder **coders, t_input *input)
{
	int	i;

	i = 0;
	input->start = get_time(0);
	while (i < input->coders_count)
	{
		pthread_create(&coders[i]->coder_thread, NULL, run_stages, coders[i]);
		i++;
	}
	i = 0;
	while (i < input->coders_count)
	{
		pthread_join(coders[i]->coder_thread, NULL);
		i++;
	}
	return ;
}
