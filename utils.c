/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:57:47 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/03 14:24:41 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"
#include <stdio.h>

long long	get_time(long start)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((tv.tv_usec / 1000) + (tv.tv_sec * 1000)) - start);
}

void	*burn_out(void *arg)
{
	t_coder	**coders;
	int		i;
	int		limit;

	i = 0;
	coders = arg;
	limit = coders[0]->values->number_of_coders;
	while (1)
	{
		if (i == limit)
			i = 0;
		if (get_time(coders[i]->start) / (coders[i]->done + 1) >= limit)
		{
			printf("i + 1 burn out\n");
			break ;
		}
		i++;
	}
	return (NULL);
}
