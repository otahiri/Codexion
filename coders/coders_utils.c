/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 10:00:56 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 10:13:24 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	*create_coder(t_input *input, int id)
{
	t_coder	*coder;

	coder = malloc(sizeof(t_coder));
	if (!coder)
		return (NULL);
	coder->compiles_done = 0;
	coder->id = id;
	coder->sleep = malloc(sizeof(t_mutex));
	if (!coder->sleep)
	{
		free(coder);
		return (NULL);
	}
	coder->lock = malloc(sizeof(t_mutex));
	if (!coder->lock)
	{
		free(coder->sleep);
		free(coder);
		return (NULL);
	}
	coder->input = input;
	coder->request = get_time(input->start, input);
	coder->right = create_dongle(input);
	return (coder);
}
