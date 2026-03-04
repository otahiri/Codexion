/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:27:15 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/04 14:10:39 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

t_coder	**push_coder(t_coder **coders, t_coder *new, int size)
{
	t_coder	**res;
	int		i;

	res = malloc(sizeof(void *) * (size + 1));
	i = 0;
	while (i <= size)
	{
		res[i] = coders[i];
		i++;
	}
	res[i] = new;
	free(coders);
	return (res);
}

t_coder	**pop_coder(t_coder **coders, int size, int target)
{
	t_coder	**res;
	int		i;
	int		j;

	res = malloc(sizeof(void *) * (size - 1));
	i = 0;
	j = 0;
	while (i < size)
	{
		if (i == target)
		{
			i++;
			continue ;
		}
		res[j] = coders[i];
		i++;
		j++;
	}
	free(coders[target]);
	free(coders);
	return (res);
}
