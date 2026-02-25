/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 12:33:42 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/25 12:14:14 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <pthread.h>
#include <stdio.h>

void	*foo(void *arg)
{
	(void)arg;
	printf("Thread is running.\n");
	return (NULL);
}

int	main(void)
{
	pthread_t	thread1;

	pthread_create(&thread1, NULL, foo, NULL);
	pthread_join(thread1, NULL);
	return (0);
}
