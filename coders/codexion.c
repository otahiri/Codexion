/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:14:23 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/30 12:01:22 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_coder	**make_coders(t_input *input)
{
	int		i;
	t_coder	**coders;

	i = 0;
	coders = malloc(sizeof(t_coder *) * (input->number_of_coders + 1));
	if (!coders)
		return (NULL);
	while (i <= input->number_of_coders)
		coders[i++] = NULL;
	return (coders);
}

static t_coder	**initialize_coders(t_input *input, t_flag *flag)
{
	t_coder	**coders;
	int		i;

	i = 0;
	coders = make_coders(input);
	if (!coders)
		return (NULL);
	while (i < input->number_of_coders)
	{
		coders[i] = create_coder(input, i + 1);
		if (!coders[i])
			return ((void *)(long)free_all(coders, input, flag));
		i++;
	}
	i = 0;
	while (coders[i])
	{
		coders[i]->left = coders[(i + input->number_of_coders + 1)
			% input->number_of_coders]->right;
		i++;
	}
	return (coders);
}

static int	start_sim(t_coder **coders, t_input *input, t_flag *flag)
{
	int			i;
	pthread_t	burnout_monitor;

	i = 0;
	while (coders[i])
	{
		if (pthread_create(&coders[i]->thread, NULL, run_stages, coders[i]))
			return (join_thread(coders, i, input));
		i++;
	}
	i = 0;
	if (input->number_of_coders == 1)
	{
		activate_switch(flag, " burned out");
		usleep(input->time_to_burnout * 1000);
	}
	extra_for_sim(coders, input, flag);
	if (pthread_create(&burnout_monitor, NULL, monitoring, coders))
		return (join_thread(coders, input->number_of_coders, input));
	while (coders[i])
		pthread_join(coders[i++]->thread, NULL);
	pthread_join(burnout_monitor, NULL);
	return (1);
}

static int	extra(t_coder **coders, t_input *input, t_flag *flag)
{
	if (!start_sim(coders, input, flag))
	{
		free_all(coders, input, flag);
		return (1);
	}
	free_all(coders, input, flag);
	return (0);
}

int	main(int argc, char **argv)
{
	t_coder	**coders;
	t_input	*input;
	t_flag	*flag;

	input = parse_input(argv, argc);
	coders = NULL;
	flag = create_flag();
	if (!flag)
	{
		free_all(coders, input, NULL);
		return (0);
	}
	if (!input)
	{
		free_flag(flag);
		return (0);
	}
	coders = initialize_coders(input, flag);
	if (!coders)
		return (0);
	return (extra(coders, input, flag));
}
