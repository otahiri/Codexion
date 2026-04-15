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

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dst;

	i = 0;
	dst = malloc(sizeof(char) * (strlen(src) + 1));
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *s1, char *s2)
{
	int		i;
	int		l;
	char	*res;

	res = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 2));
	i = 0;
	l = 0;
	while (s1[i])
		res[l++] = s1[i++];
	res[l++] = ' ';
	i = 0;
	while (s2[i])
		res[l++] = s2[i++];
	return (res);
}

long	get_time(long time_stamp, t_input *input)
{
	struct timeval	tv;
	int				res;

	res = gettimeofday(&tv, NULL);
	if (res)
	{
		activate_switch(input, "gettimeofday failed\n");
		return (0);
	}
	return (((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - time_stamp);
}

void	ft_usleep(long timer, t_coder *coder)
{
	struct timeval	tv;
	struct timespec	ts;

	gettimeofday(&tv, NULL);
	ts.tv_sec = time(NULL) + timer / 1000;
	ts.tv_nsec = tv.tv_usec * 1000 + 1000 * 1000 * (timer % 1000);
	ts.tv_sec += ts.tv_nsec / (1000 * 1000 * 1000);
	ts.tv_nsec %= (1000 * 1000 * 1000);
	if (check_switch(coder->input))
		return ;
	pthread_cond_timedwait(&coder->sleep->cond, &coder->sleep->mutex, &ts);
}
