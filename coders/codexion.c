/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:14:23 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 10:18:27 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	t_coder	*codera;
	t_coder	*coderb;
	t_coder	*coderc;
	t_input	*input;
	t_heap	*heap;

	input = parse_input(argv, argc);
	if (!input)
		return (0);
	input->start = get_time(0, input);
	heap = create_heap(input);
	codera = create_coder(input, 1);
	coderb = create_coder(input, 2);
	coderc = create_coder(input, 3);
	coderc->request = get_time(input->start, input);
	usleep(5000);
	codera->request = get_time(input->start, input);
	usleep(5000);
	coderb->request = get_time(input->start, input);
	heap_insert(heap, coderb, input);
	heap_insert(heap, codera, input);
	heap_insert(heap, coderc, input);
	for (int i = 0; i < 3; i++)
		printf("coder %d time is %ld\n", heap->coders[i]->id, heap->coders[i]->request);
}
