/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:14:23 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/21 15:08:03 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

t_coder	**initialize_coders(t_input *input)
{
	t_coder			**coders;
	int				i;

	i = 0;
	coders = malloc(sizeof(t_coder) * (input->number_of_coders + 1));
	if (!coders)
		return (NULL);
	while (coders[i])
	{
		coders[i] = create_coder(input, i + 1);
		i++;
	}
	coders[i] = NULL;
	i = 0;
	while (coders[i])
	{
		coders[i]->left = coders[(i + input->number_of_coders + 1)
			% input->number_of_coders]->right;
		i++;
	}
	return (coders);
}

void	free_all(t_coder **coders, t_input *input)
{
	int	i;

	i = 0;
	free_mutex(coders[0]->flag->lock);
	free(coders[0]->flag->dialogue);
	free(coders[0]->flag);
	while (coders[i])
		free_coder(coders[i++]);
	free(coders);
	free(input->scheduler);
	free_mutex(input->write_lock);
	free(input);
}

void	start_sim(t_coder **coders, t_input *input, t_flag *flag)
{
	int			i;
	pthread_t	burnout_monitor;

	i = 0;
	input->start = get_time(0, input);
	while (coders[i])
	{
		coders[i]->flag = flag;
		pthread_create(&coders[i]->thread, NULL, run_stages, coders[i]);
		i++;
	}
	i = 0;
	pthread_create(&burnout_monitor, NULL, monitoring, coders);
	while (coders[i])
	{
		pthread_join(coders[i]->thread, NULL);
		i++;
	}
	pthread_join(burnout_monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_coder	**coders;
	t_input	*input;
	t_flag	*flag;

	input = parse_input(argv, argc);
	if (!input)
		return (0);
	if (input->number_of_coders < 2 || input->time_to_burnout == 0)
	{
		free_all(NULL, input);
		return (0);
	}
	flag = create_flag();
	if (!flag)
	{
		free(input);
		return (0);
	}
	coders = initialize_coders(input);
	if (!coders)
	{
		free(input);
		return (0);
	}
	start_sim(coders, input, flag);
	free_all(coders, input);
}
