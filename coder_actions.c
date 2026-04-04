/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:58:55 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/03 15:26:27 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*run_stages(void *args)
{
	t_coder	*coder;

	coder = args;
	while (coder->compile_count < coder->input->compile_count)
	{
		printf("running stages for %dth time\n", coder->compile_count);
		usleep(900);
		coder->compile_count++;
	}
	return (NULL);
}

void	run_coders(t_coder **coders, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->coders_count)
	{
		pthread_create(&coders[i]->coder_thread, NULL, run_stages, coders[i]);
		i++;
	}
	while (i < input->coders_count)
		pthread_join(coders[i++]->coder_thread, NULL);
	return ;
}
