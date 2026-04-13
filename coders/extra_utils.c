/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 18:55:04 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 18:59:02 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_valid_number(char *num)
{
	while (*num)
	{
		if (!ft_isdigit(*num))
			return (0);
		num++;
	}
	return (1);
}

char	*ft_strcpy(const char *src, char *dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

long	get_time(long time_stamp, t_input *input)
{
	struct timeval	tv;
	int				res;

	res = gettimeofday(&tv, NULL);
	if (res)
	{
		pthread_mutex_lock(&input->kill_switch->switch_lock);
		input->kill_switch->turn_off = 1;
		pthread_mutex_unlock(&input->kill_switch->switch_lock);
		return (-1);
	}
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time_stamp);
}

void	ft_usleep(long timer, t_input *input)
{
	while (timer > 0)
	{
		if (input->kill_switch->turn_off)
			return ;
		if (usleep(1000) == -1)
			activate_switch(input);
		timer -= 1000;
	}
}
