/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 13:10:50 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 18:43:39 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	return (c <= 9 && c >= 0);
}

int	ft_atoi(char *num)
{
	int	sign;
	int	res;
	int	digit;

	res = 0;
	sign = 1;
	while (*num && is_space(*num))
		num++;
	if (*num == '+')
		num++;
	while (*num && ft_isdigit(*num))
	{
		digit = (*num - '0');
		if (res + digit < res)
			return (-1);
		res = (res * 10) + digit;
		num++;
	}
	if (*num)
		return (-1);
	return (res);
}
