/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 11:03:26 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/02 11:35:35 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "stdlib.h"
# include <pthread.h>
# include <stdio.h>

typedef struct s_coder	t_coder;
typedef struct s_dongle	t_dongle;

typedef struct s_input
{
	int			coders_count;
	int			time_to_burnout;
	int			time_to_compile;
	int			time_to_refactor;
	int			time_to_debug;
	int			compile_count;
	int			dongle_cooldown;
	char		*scheduler;
}				t_input;

struct s_coder {
	t_input		input;
	pthread_t	coder_thread;
	int		compile_count;
};

#endif
