/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:20:09 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/21 15:05:01 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	activate_switch(t_flag *flag, char *dialogue)
{
	pthread_mutex_lock(&flag->lock->mutex);
	flag->off++;
	flag->dialogue = ft_strdup(dialogue);
	pthread_mutex_unlock(&flag->lock->mutex);
	return (1);
}

int	check_switch(t_flag *flag)
{
	pthread_mutex_lock(&flag->lock->mutex);
	if (flag->off)
	{
		pthread_mutex_unlock(&flag->lock->mutex);
		return (1);
	}
	pthread_mutex_unlock(&flag->lock->mutex);
	return (0);
}

t_flag	*create_flag(void)
{
	t_flag	*flag;

	flag = malloc(sizeof(t_flag));
	if (!flag)
		return (NULL);
	flag->lock = create_mutex();
	if (!flag->lock)
	{
		free(flag);
		return (NULL);
	}
	flag->off = 0;
	return (flag);
}
