/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 09:49:40 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/24 13:38:12 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef enum s_stage
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
}					t_stage;

typedef struct s_dongle
{
	pthread_mutex_t	dongle;
	int				cooldown;
}					t_dongle;

typedef struct s_input
{
	int				number_of_coders;
	int				time_to_burnout;
	int				time_to_compile;
	int				time_to_debug;
	int				time_to_refactor;
	int				number_of_compiles_required;
	int				dongle_cooldown;
	const char		*scheduler;
}					t_input;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				done;
	t_input			*values;
}					t_coder;

t_input				*parse(char **argv);

#endif
