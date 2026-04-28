/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:22:39 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 15:11:40 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "codexion.h"

int	is_valid_number(char *num)
{
	if (*num == '+')
		return (1);
	while (*num)
	{
		if (!ft_isdigit(*num))
			return (0);
		num++;
	}
	return (1);
}

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * (strlen(src) + 1));
	if (!dst)
		return (NULL);
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

	(void)input;
	gettimeofday(&tv, NULL);
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time_stamp);
}

void	ft_usleep(long timer, t_coder *coder)
{
	struct timeval	tv;
	struct timespec	ts;

	gettimeofday(&tv, NULL);
	ts.tv_sec = tv.tv_sec + timer / 1000;
	ts.tv_nsec = tv.tv_usec * 1000 + 1000 * 1000 * (timer % 1000);
	ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
	ts.tv_nsec %= (1000 * 1000 * 1000);
	pthread_mutex_lock(&coder->sleep->mutex);
	pthread_cond_timedwait(&coder->sleep->cond, &coder->sleep->mutex, &ts);
	pthread_mutex_unlock(&coder->sleep->mutex);
}
