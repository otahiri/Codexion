/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:57:47 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/27 11:58:22 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

long	get_time(long start)
{
	struct timeval	tv;
	struct timezone	tz;
	long			now;

	gettimeofday(&tv, &tz);
	now = tv.tv_usec;
	return (now - start);
}
