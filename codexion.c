/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:06:00 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 18:51:53 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_input	*input;

	if (argc != 9)
		return (0);
	input = parse_input(argv);
	if (!input)
		return (0);
	printf("number of coder is %d\ntime to compile is %d\n timer to refactor is %d\n time to debug is %d\n compile count is %d\n dongle cooldown is %d\n scheduler is %s", input->coders_count, input->time_to_compile, input->time_to_refactor, input->time_to_debug, input->compile_count, input->dongle_cooldown, input->scheduler);
	return (0);
}
