/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_coders.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 12:58:55 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/03 13:24:28 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

void	run_coders(t_coder **coders, t_input *input)
{
	int	i;

	i = 0;
	while (i < input->coders_count)
	{
		pthread_create(&coders[i]->coder_thread, NULL, NULL, coders[i]);
		i++;
	}
	return ;
}
