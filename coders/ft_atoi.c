/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 08:14:03 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/18 08:23:22 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	return (c <= '9' && c >= '0');
}

int	ft_atoi(char *num)
{
	int	res;
	int	digit;

	res = 0;
	while (*num && is_space(*num))
		num++;
	if (*num == '+')
		num++;
	while (*num && ft_isdigit(*num))
	{
		digit = (*num - '0');
		if (res + digit < 0)
			return (-1);
		res = (res * 10) + digit;
		num++;
	}
	if (*num)
		return (-1);
	return (res);
}
