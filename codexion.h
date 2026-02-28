/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otahiri- <otahiri-@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 09:49:40 by otahiri-          #+#    #+#             */
/*   Updated: 2026/02/28 15:27:09 by otahiri-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef enum s_stage
{
	COMPILING,
	DEBUGGING,
	REFACTORING,
}					t_stage;

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
	pthread_mutex_t	*dongles;
}					t_input;

typedef struct s_coder
{
	pthread_t		thread;
	int				id;
	int				done;
	t_input			*values;
	long			start;
	pthread_mutex_t	*left_hand;
	pthread_mutex_t	*right_hand;
}					t_coder;

t_input				*parse(char **argv);
void				compile(t_coder *coder);
void				debug(t_coder *coder);
void				refactor(t_coder *coder);
void				*run_coder(void *arg);
long long			get_time(long long start);

#endif
