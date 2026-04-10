/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burn_out_monitor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:01:14 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/09 11:07:10 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*monitoring(void *arg)
{
	t_coder	**coders;
	t_input	*input;
	int		i;

	coders = arg;
	input = coders[0]->input;
	while (1)
	{
		i = 0;
		while (i < input->coders_count)
		{
			if (coders[i]->last_compile + input->time_to_burnout < get_time(0,
					input))
			{
				printf("%ld is the current burn out time left  for %d\n", coders[i]->last_compile + input->time_to_burnout - get_time(0, input), coders[i]->id);
				pthread_mutex_lock(&input->kill_switch->switch_lock);
				printf("%ld %d burned out\n", get_time(input->start, input),
					coders[i]->id);
				input->kill_switch->kill_switch = 1;
				pthread_mutex_lock(&input->kill_switch->switch_lock);
				return (NULL);
			}
			i++;
			usleep(1000);
		}
	}
}
