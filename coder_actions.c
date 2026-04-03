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

void	run_coders(t_coder **coders, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->coders_count)
	{
		pthread_create(&coders[i]->coder_thread, NULL, NULL, coders[i]);
		i++;
	}
	while (i < input->coders_count)
		pthread_join(coders[i++]->coder_thread, NULL);
	return ;
}
