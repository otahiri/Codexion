/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:58:55 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/04 10:08:13 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*run_stages(void *args)
{
	t_coder	*coder;

	coder = args;
	if (!(coder->id % 2))
		usleep(1000);
	while (coder->compile_count < coder->input->number_of_compiles_required)
	{
		compile(coder);
		debug(coder);
		refactor(coder);
		coder->compile_count++;
	}
	return (NULL);
}

void	run_coders(t_coder **coders, t_input *input)
{
	int			i;
	pthread_t	burn_out;

	i = 0;
	while (i < input->coders_count)
	{
		pthread_create(&coders[i]->coder_thread, NULL, run_stages,
			coders[i]);
		i++;
	}
	pthread_create(&burn_out, NULL, monitoring, coders);
	pthread_join(burn_out, NULL);
	i = 0;
	while (i < input->coders_count)
	{
		pthread_join(coders[i]->coder_thread, NULL);
		i++;
	}
	return ;
}
