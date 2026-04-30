/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_four.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:54:11 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/30 11:54:20 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

void	init_value(t_heap *heap, t_input *input)
{
	int	i;

	i = 0;
	heap->size = 0;
	while (i <= input->number_of_coders)
		heap->coders[i++] = NULL;
}
