/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:58:05 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 15:11:20 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_mutex	*create_mutex(void)
{
	t_mutex	*mutex;

	mutex = malloc(sizeof(t_mutex));
	if (!mutex)
		return (NULL);
	pthread_mutex_init(&mutex->mutex, NULL);
	pthread_cond_init(&mutex->cond, NULL);
	return (mutex);
}

void	free_mutex(t_mutex *mutex)
{
	pthread_mutex_destroy(&mutex->mutex);
	pthread_cond_destroy(&mutex->cond);
	free(mutex);
}
