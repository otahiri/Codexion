/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 08:14:36 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/15 14:52:56 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

void	compile(t_coder *coder)
{
	long			time;

	if (coder->left == coder->right)
		activate_switch(coder->input, "1 burned out\n");
	if (check_switch(coder->input))
		return ;
	acquire_dongle(coder->left, coder);
	acquire_dongle(coder->right, coder);
	time = get_time(coder->input->start, coder->input);
	if (check_switch(coder->input))
		return ;
	printf("%ld %d is compiling\n", time, coder->id);
	ft_usleep(coder->input->time_to_compile, coder);
	coder->last_compile = get_time(0, coder->input);
	release_dongle(coder->right, coder->input);
	release_dongle(coder->left, coder->input);
}

void	refactor(t_coder *coder)
{
	long			time;

	time = get_time(coder->input->start, coder->input);
	if (check_switch(coder->input))
		return ;
	printf("%ld %d is refactoring\n", time, coder->id);
	ft_usleep(coder->input->time_to_refactor, coder);
}

void	debug(t_coder *coder)
{
	long			time;

	time = get_time(coder->input->start, coder->input);
	if (check_switch(coder->input))
		return ;
	printf("%ld %d is debugging\n", time, coder->id);
	ft_usleep(coder->input->time_to_debug, coder);
}
