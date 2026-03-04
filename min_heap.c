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

void	push_coder(t_dongle *dongle, t_coder *coder)
{
	if (!dongle->heap[1])
		dongle->heap[1] = coder;
}

void	pop_coder(t_dongle *dongle, t_coder *coder)
{
	int	target;

	target = 0;
	while (target < 2)
	{
		if ((t_coder *)(dongle->heap[target])->id == coder->id)
			break;
		target++;
	}
	dongle->heap[target] = NULL;
	if (target == 0 && dongle->heap[1])
	{
		dongle->heap[0] = dongle->heap[1];
		dongle->heap[1] = NULL;
	}
}
