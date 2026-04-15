/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 10:25:53 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/15 10:46:01 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = strlen(str) - 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char	*ft_itoa(long n)
{
	size_t	i;
	char	*nbr;
	long	num;
	int		is_first_digit;

	nbr = malloc(12);
	if (nbr == NULL)
		return (NULL);
	num = (long)n;
	i = 0;
	if (num < 0)
		num = -num;
	is_first_digit = 1;
	while (num > 0 || is_first_digit)
	{
		nbr[i++] = '0' + num % 10;
		is_first_digit = 0;
		num /= 10;
	}
	if (n < 0)
		nbr[i++] = '-';
	nbr[i] = '\0';
	ft_strrev(nbr);
	return (nbr);
}
