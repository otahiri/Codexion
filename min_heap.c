/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_heap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 13:27:15 by otahiri-          #+#    #+#             */
/*   Updated: 2026/03/06 13:03:33 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

static void	calculate_priority(t_dongle *dongle)
{
	int	i;

	i = 0;
	while (i < dongle->heap_size)
	{
		if (!strcmp(dongle->heap[i]->values->scheduler, "fifo"))
			dongle->heap[i]->priority = (dongle->heap[i]->request_time
					- get_time(0));
		if (!strcmp(dongle->heap[i]->values->scheduler, "edf"))
			dongle->heap[i]->priority = (dongle->heap[i]->last_compile
					- get_time(0));
		i++;
	}
}

static void	sort_heap(t_dongle *dongle)
{
	int		i;
	int		j;
	void	*tmp;

	i = 0;
	calculate_priority(dongle);
	while (i < dongle->heap_size)
	{
		j = 0;
		while (j < dongle->heap_size - 1)
		{
			if (dongle->heap[j]->priority > dongle->heap[j + 1]->priority)
			{
				tmp = dongle->heap[j];
				dongle->heap[j] = dongle->heap[j + 1];
				dongle->heap[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	push_coder(t_dongle *dongle, t_coder *coder)
{
	dongle->heap[dongle->heap_size] = coder;
	dongle->heap_size++;
	sort_heap(dongle);
}

void	pop_coder(t_dongle *dongle)
{
	if (!dongle->heap_size)
		return ;
	dongle->heap[0] = dongle->heap[dongle->heap_size - 1];
	dongle->heap[dongle->heap_size - 1] = NULL;
	dongle->heap_size--;
	if (dongle->heap_size > 1)
		sort_heap(dongle);
}

t_coder	*peak_top(t_dongle *dongle)
{
	if (dongle->heap_size)
		return (dongle->heap[0]);
	return (NULL);
}
