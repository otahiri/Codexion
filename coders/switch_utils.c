/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 09:36:26 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/14 09:36:50 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	activate_switch(t_input *input, char *dialogue)
{
	pthread_mutex_lock(&input->kill_switch->switch_lock);
	input->kill_switch->dialogue = ft_strcat(ft_itoa(get_time(input->start,
					input)), ft_strdup(dialogue));
	input->kill_switch->turn_off++;
	pthread_mutex_unlock(&input->kill_switch->switch_lock);
	return (1);
}

int	check_switch(t_input *input)
{
	pthread_mutex_lock(&input->kill_switch->switch_lock);
	if (input->kill_switch->turn_off)
	{
		pthread_mutex_unlock(&input->kill_switch->switch_lock);
		return (1);
	}
	pthread_mutex_unlock(&input->kill_switch->switch_lock);
	return (0);
}
