/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:13:33 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/19 11:26:05 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	compile(t_coder *coder)
{
	aquire_dongles(coder);
	coder->last_compile = get_time(coder->input->start, coder->input);
	printf("%ld %d is compiling\n", get_time(coder->input->start, coder->input),
		coder->id);
	ft_usleep(coder->input->time_to_compile, coder);
	release_dongle(coder);
}

void	*run_stages(void *args)
{
	t_coder			*coder;

	coder = args;
	if ((coder->id % 2))
		ft_usleep(10, coder);
	while (coder->compiles_done < coder->input->number_of_compiles_required)
	{
		compile(coder);
		coder->compiles_done++;
	}
	return (NULL);
}
