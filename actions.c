/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 08:14:36 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/04 10:04:35 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long	get_time(long time_stamp)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time_stamp);
}

void	compile(t_coder *coder)
{
	printf("%ld %d is compiling\n", get_time(coder->input->start), coder->id);
	usleep(coder->input->time_to_compile * 1000);
}

void	refactor(t_coder *coder)
{
	printf("%ld %d is refactoring\n", get_time(coder->input->start), coder->id);
	usleep(coder->input->time_to_refactor * 1000);
}

void	debug(t_coder *coder)
{
	printf("%ld %d is debuggin\n", get_time(coder->input->start), coder->id);
	usleep(coder->input->time_to_debug * 1000);
}
