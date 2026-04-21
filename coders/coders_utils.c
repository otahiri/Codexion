/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:00:56 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 15:11:37 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <pthread.h>

t_coder	*create_coder(t_input *input, int id)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->compiles_done = 0;
	coder->id = id;
	coder->sleep = create_mutex();
	if (!coder->sleep)
	{
		free(coder);
		return (NULL);
	}
	coder->lock = create_mutex();
	if (!coder->lock)
	{
		free(coder->sleep);
		free(coder);
		return (NULL);
	}
	coder->input = input;
	coder->request = get_time(0, input);
	coder->last_compile = get_time(0, input);
	coder->right = create_dongle(input);
	return (coder);
}

void	free_coder(t_coder *coder)
{
	free_mutex(coder->sleep);
	free_mutex(coder->lock);
	free_dongle(coder->right);
	free(coder);
}
