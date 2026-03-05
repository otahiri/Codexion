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

static void	sort_heap(t_dongle *dongle)
{
	return ;
}

void	push_coder(t_dongle *dongle, t_coder *coder)
{
	if (!dongle->heap_size)
		return ;
	if (!dongle->heap[dongle->heap_size - 1])
		dongle->heap[dongle->heap_size - 1] = coder;
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
