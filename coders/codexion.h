/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 16:15:09 by otahiri-          #+#    #+#             */
/*   Updated: 2026/04/16 16:33:11 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include "stdio.h"
# include "stdlib.h"
# include "string.h"
# include "unistd.h"
# include <pthread.h>

typedef struct s_coder		t_coder;
typedef struct s_input		t_input;
typedef struct s_simulation	t_simulation;
typedef struct s_dongle		t_dongle;
typedef struct s_heap		t_heap;
typedef struct s_mutex		t_mutex;
typedef struct s_off		t_off;

struct						s_input
{
	int						number_of_coders;
	int						time_to_burnout;
	int						time_to_compile;
	int						time_to_debug;
	int						time_to_refactor;
	int						number_of_compiles_required;
	int						dongle_cooldown;
	char					*scheduler;
};

struct						s_mutex
{
	pthread_mutex_t			mutex;
	pthread_cond_t			cond;
};

struct						s_heap
{
	t_coder					**coders;
	int						size;
	int						cap;
	t_mutex			*sleep;
	t_input			*input;
};

struct						s_dongle
{
	t_mutex					*lock;
	int						cooldown;
	s_heap					*heap;
	long					next_available;
};

typedef struct s_monitoring
{
	t_simulation	*simulation;
	t_mutex		*lock;
}							t_monitoring;

struct						s_off
{
	pthread_mutex_t			lock;
	int						off;
};

#endif
