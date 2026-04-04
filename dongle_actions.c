/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_actions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/04 11:12:38 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/04 11:45:28 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	acquire_dongle(t_dongle *dongle)
{
	if (dongle->cooldown < 0)
		pthread_cond_wait(&dongle->lock->cond, NULL);
	else if (dongle->cooldown > 0)
	{
	}
}
